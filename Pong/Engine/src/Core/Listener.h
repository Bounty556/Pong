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
		~Listener();

		void Subscribe(const char* message, std::function<void(void*)> callback);
		void Unsubscribe(const char* message);

		void Response(const char* message, void* data);

	private:
		Map<const char*, std::function<void(void*)>> m_Callbacks;
	};
}