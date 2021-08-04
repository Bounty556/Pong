#pragma once

#include <Defines.h>
#include <Structures/Map.h>
#include <Structures/Vector.h>
#include <Structures/Queue.h>

namespace Soul
{
	class Listener;

	class SOULAPI MessageBus
	{
	public:
		struct Message
		{
			const char* message;
			void* data;
			f32 time;
		};

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
		static void QueueMessage(const char* message, void* data, f32 time = 0.0f);

		/*
		Send a message directly to a listener without going through the queue.
		*/
		static void ImmediateMessage(const char* message, void* data);

		/*
		Erases all messages and any pending data they may have stored.
		*/
		static void ClearQueue();

		/*
		Updates messages in the queue. Those whose time is out are sent out and
		removed.
		*/
		static void PumpQueue(f32 dt);
		
	private:
		static bool m_IsInitialized;
		static Map<const char*, Vector<Listener*>>* m_Map;
		static Queue<Message>* m_Messages;
		static Vector<Message>* m_TimedMessages;
	};
}