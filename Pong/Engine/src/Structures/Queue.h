#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>

// TODO: There may be some issues with storing objects in here that have non-copyable data, or with very deep data stored in them. May need to investigate and some more testing with this class.

namespace Soul
{
	template <class T>
	class Queue
	{
	public:
		Queue(u16 capacity = 32);
		Queue(const Queue&) = delete;
		Queue(Queue&& otherQueue);

		Queue& operator=(const Queue&) = delete;
		Queue& operator=(Queue&& otherQueue);

		/*
		Queueing/Dequeueing elements
		*/
		void Que(const T& element);
		void Que(T&& element);
		T&& Deque();
		T& Peek();
		const T& Peek() const;

		u16 Count() const;
		bool Empty() const;

	private:
		u16 m_Capacity;
		u16 m_Size;
		u16 m_Head;
		u16 m_Tail;

		UniquePointer<T> m_Queue;
	};

	template <class T>
	Queue<T>::Queue(u16 capacity /* = 32 */) :
		m_Capacity(capacity),
		m_Size(0),
		m_Queue(PARTITION_ARRAY(T, capacity)),
		m_Head(0),
		m_Tail(0)
	{
	}

	template <class T>
	Queue<T>::Queue(Queue&& otherQueue) :
		m_Capacity(otherQueue.m_Capacity),
		m_Size(otherQueue.m_Size),
		m_Queue(std::move(otherQueue.m_Queue)),
		m_Head(otherQueue.m_Head),
		m_Tail(otherQueue.m_Tail)
	{
		otherQueue.m_Capacity = 0;
		otherQueue.m_Size = 0;
	}

	template <class T>
	Queue<T>& Queue<T>::operator=(Queue&& otherQueue)
	{
		m_Capacity = otherQueue.m_Capacity;
		m_Size = otherQueue.m_Size;
		m_Queue = std::move(otherQueue.m_Queue);
		m_Head = otherQueue.m_Head;
		m_Tail = otherQueue.m_Tail;
		otherQueue.m_Capacity = 0;
		otherQueue.m_Size = 0;
	}

	template <class T>
	void Queue<T>::Que(const T& element)
	{
		ASSERT(m_Size < m_Capacity);

		// Add element at Queue head
		new (&m_Queue[m_Head]) T(element);
		m_Size = (m_Size + 1) % m_Capacity;
	}

	template <class T>
	void Queue<T>::Que(T&& element)
	{
		ASSERT(m_Size < m_Capacity);

		// Add element at Queue head
		new (&m_Queue[m_Head]) T(std::move(element));
		m_Size = (m_Size + 1) % m_Capacity;
	}

	template <class T>
	T&& Queue<T>::Deque()
	{
		ASSERT(m_Size > 0);

		// Remove element at tail
		u16 oldTail = m_Tail;
		m_Tail = (m_Tail + 1) % m_Capacity;
		m_Size--;
		return std::move(m_Queue[oldTail]);
	}

	template <class T>
	T& Queue<T>::Peek()
	{
		return m_Queue[m_Tail];
	}

	template <class T>
	const T& Queue<T>::Peek() const
	{
		return m_Queue[m_Tail];
	}

	template <class T>
	u16 Queue<T>::Count() const
	{
		return m_Size;
	}

	template <class T>
	bool Queue<T>::Empty() const
	{
		return m_Size == 0;
	}
}