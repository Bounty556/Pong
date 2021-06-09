#pragma once

#include <Defines.h>
#include <Structures/Map.h>

namespace Soul
{
	class Listener;
	template <class K> // TODO: Remove
	class Vector;

	class SOULAPI MessageBus
	{
	public:
		MessageBus() = delete;

		/*
		Start up the MessageBus.
		*/
		static bool Initialize();

		/*
		Cleans up the MessageBus.
		*/
		static void Shutdown();

		/*
		Makes the listener start listening for the provided message.
		*/
		static void Subscribe(const char* message, Listener* listener);

		/*
		Stop the listener from listening to the provided message.
		*/
		static void Unsubscribe(const char* message, Listener* listener);
		
		/*
		Queue a message up to be pumped later.
		*/
		static void QueueMessage(const char* message, void* data);

		/*
		Send a message directly to a listener without going through the queue.
		*/
		static void ImmediateMessage(const char* message, void* data);

		/*
		Sends all messages in the queue out, effectively emptying it.
		*/
		static void PumpQueue();
		
	private:
		static Map<const char*, Vector<Listener*>>* m_Map;
	};
}