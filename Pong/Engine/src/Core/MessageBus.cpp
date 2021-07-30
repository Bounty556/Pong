#include "MessageBus.h"

#include <Core/Listener.h>

#define MessageBusMap Map<const char*, Vector<Listener*>>

namespace Soul
{
	Map<const char*, Vector<Listener*>>* MessageBus::m_Map;
	Queue<MessageBus::Message>* MessageBus::m_Messages;

	bool MessageBus::Initialize()
	{
		m_Map = NEW(MessageBusMap);
		m_Messages = NEW(Queue<MessageBus::Message>, 64);

		return true;
	}

	void MessageBus::Shutdown()
	{
		DELETE(m_Map);
		DELETE(m_Messages);
	}

	void MessageBus::Subscribe(const char* message, Listener* listener)
	{
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
		// Find the listener list in the map.
		Vector<Listener*>* listeners = m_Map->GetValue(message);
		
		// If we found it, remove the listener
		if (listeners)
			listeners->Remove(listener);
	}

	void MessageBus::QueueMessage(const char* message, void* data, f32 time /*=0.0f*/)
	{
		m_Messages->Que(Message{ message, data, time});
	}

	void MessageBus::ImmediateMessage(const char* message, void* data)
	{
		Vector<Listener*>* listeners = m_Map->GetValue(message);

		if (listeners)
			for (u32 i = 0; i < listeners->Count(); ++i)
				(*listeners)[i]->Response(message, data);

		if (data)
			DELETE(data);
	}
	
	void MessageBus::PumpQueue(f32 dt)
	{
		Vector<Message> messagesLeft;

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
				messagesLeft.Push(message);
		}

		while (!messagesLeft.IsEmpty())
			m_Messages->Que(messagesLeft.Pop());
	}
}