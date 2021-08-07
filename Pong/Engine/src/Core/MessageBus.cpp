#include "MessageBus.h"

#include <Core/Listener.h>

#define MessageBusMap Map<const char*, Vector<Listener*>>

namespace Soul
{
	bool MessageBus::m_IsInitialized = false;
	Map<const char*, Vector<Listener*>>* MessageBus::m_Map;
	Queue<MessageBus::Message>* MessageBus::m_Messages;
	Vector<MessageBus::Message>* MessageBus::m_TimedMessages;

	bool MessageBus::Initialize()
	{
		ASSERT(!m_IsInitialized);
		m_IsInitialized = true;

		m_Map = NEW(MessageBusMap);
		m_Messages = NEW(Queue<MessageBus::Message>, 64);
		m_TimedMessages = NEW(Vector<MessageBus::Message>, 64);

		return true;
	}

	void MessageBus::Shutdown()
	{
		ASSERT(m_IsInitialized);

		ClearQueue();
		DELETE(m_Map);
		DELETE(m_Messages);
		DELETE(m_TimedMessages);

		m_IsInitialized = false;
	}

	void MessageBus::Subscribe(const char* message, Listener* listener)
	{
		ASSERT(m_IsInitialized);

		// Find a spot in the map
		Vector<Listener*>* listeners = m_Map->GetValue(message);

		// If the spot contains a vector, add the listener to the vector
		if (listeners)
			listeners->Push(listener);
		else
		{
			// If the spot is empty, create a new vector and add the listener
			Vector<Listener*> newList;
			newList.Push(listener);
			m_Map->AddPair(message, std::move(newList));
		}
	}

	void MessageBus::Unsubscribe(const char* message, Listener* listener)
	{
		ASSERT(m_IsInitialized);

		// Find the listener list in the map.
		Vector<Listener*>* listeners = m_Map->GetValue(message);
		
		// If we found it, remove the listener
		if (listeners)
			listeners->Remove(listener);
	}

	void MessageBus::QueueMessage(const char* message, void* data /*= nullptr*/, f32 time /*=0.0f*/)
	{
		ASSERT(m_IsInitialized);

		m_Messages->Que(Message{ message, data, time});
	}

	void MessageBus::ImmediateMessage(const char* message, void* data)
	{
		ASSERT(m_IsInitialized);
	
		Vector<Listener*>* listeners = m_Map->GetValue(message);

		if (listeners)
			for (u32 i = 0; i < listeners->Count(); ++i)
				(*listeners)[i]->Response(message, data);

		if (data)
			DELETE(data);
	}
	
	void MessageBus::ClearQueue()
	{
		ASSERT(m_IsInitialized);

		while (!m_Messages->IsEmpty())
		{
			Message message = m_Messages->Deque();
			if (message.data)
				DELETE(message.data);
		}

		while (!m_TimedMessages->IsEmpty())
		{
			Message message = m_TimedMessages->Pop();
			if (message.data)
				DELETE(message.data);
		}
	}

	void MessageBus::PumpQueue(f32 dt)
	{
		ASSERT(m_IsInitialized);
		
		while (!m_Messages->IsEmpty())
		{
			Message message = m_Messages->Deque();

			message.time -= dt;

			if (message.time <= 0.0f)
			{
				Vector<Listener*>* listeners = m_Map->GetValue(message.message);

				if (listeners)
					for (u32 i = 0; i < listeners->Count(); ++i)
						(*listeners)[i]->Response(message.message, message.data);

				if (message.data)
					DELETE(message.data);
			}
			else
				m_TimedMessages->Push(message);
		}

		while (!m_TimedMessages->IsEmpty())
			m_Messages->Que(m_TimedMessages->Pop());
	}
}