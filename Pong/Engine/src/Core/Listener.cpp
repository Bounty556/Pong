#include "Listener.h"

#include <Core/MessageBus.h>

namespace Soul
{
	Listener::Listener() :
		m_Callbacks()
	{
	}

	void Listener::Subscribe(const char* message, std::function<void(void*)> callback)
	{
		MessageBus::Subscribe(message, this);

		m_Callbacks.AddPair(message, std::move(callback));
	}

	void Listener::Unsubscribe(const char* message)
	{
		MessageBus::Unsubscribe(message, this);

		m_Callbacks.RemovePair(message);
	}

	void Listener::Response(const char* message, void* data)
	{
		std::function<void(void*)>* callback = m_Callbacks.GetValue(message);

		if (callback)
			(*callback)(data);
	}
}