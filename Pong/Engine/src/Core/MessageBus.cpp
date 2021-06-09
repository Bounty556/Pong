#include "MessageBus.h"

#include <Core/Listener.h>

#define MessageBusMap Map<const char*, Vector<Listener*>>

namespace Soul
{
	Map<const char*, Vector<Listener*>>* MessageBus::m_Map;

	bool MessageBus::Initialize()
	{
		m_Map = PARTITION(MessageBusMap);

		return true;
	}

	void MessageBus::Shutdown()
	{
		MemoryManager::FreeMemory(m_Map);
	}

	void MessageBus::Subscribe(const char* message, Listener* listener)
	{
		// TODO: 
	}

	void MessageBus::Unsubscribe(const char* message, Listener* listener)
	{
		// TODO:
	}

	void MessageBus::QueueMessage(const char* message, void* data)
	{
		// TODO:
	}

	void MessageBus::ImmediateMessage(const char* message, void* data)
	{
		// TODO:
	}
	
	void MessageBus::PumpQueue()
	{
		// TODO:
	}
}