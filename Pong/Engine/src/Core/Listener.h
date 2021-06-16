#pragma once

#include <Defines.h>
#include <Structures/Map.h>

#include <functional>

namespace Soul
{
	class SOULAPI Listener
	{
	public:
		Listener();

		Listener(const Listener&) = delete;
		Listener(Listener&& other) noexcept;

		Listener& operator=(const Listener&) = delete;
		Listener& operator=(Listener&& other) noexcept;

		~Listener();

		void Subscribe(const char* message, std::function<void(void*)> callback);
		void Unsubscribe(const char* message);

	private:
		void Response(const char* message, void* data);

		friend class MessageBus;

	private:
		Map<const char*, std::function<void(void*)>> m_Callbacks;
	};
}