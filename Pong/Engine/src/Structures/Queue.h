#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	template <class T>
	class Queue
	{
	public:
		Queue(u32 capacity = 8);

		Queue(const Queue&) = delete;
		Queue(Queue&& otherQueue) noexcept;

		~Queue();

		Queue& operator=(const Queue&) = delete;
		Queue& operator=(Queue&& otherQueue) noexcept;

		/*
		Queueing/Dequeueing elements
		*/
		void Que(const T& element);
		void Que(T&& element);
		T Deque();
		T& Peek();
		const T& Peek() const;
		T& PeekEnd();
		const T& PeekEnd() const;

		u16 Count() const;
		bool IsEmpty() const;

		void Clear();

	private:
		void Resize(u32 newCapacity);

	private:
		u32 m_Capacity;
		u32 m_Size;
		u32 m_Head;
		u32 m_Tail;

		UniquePointer<T> m_Queue;
	};

	template <class T>
	Queue<T>::Queue(u32 capacity /* = 32 */) :
		m_Capacity(capacity),
		m_Size(0),
		m_Head(0),
		m_Tail(0),
		m_Queue(NEW_ARRAY(T, capacity))
	{
	}

	template <class T>
	Queue<T>::Queue(Queue&& otherQueue) noexcept :
		m_Capacity(otherQueue.m_Capacity),
		m_Size(otherQueue.m_Size),
		m_Head(otherQueue.m_Head),
		m_Tail(otherQueue.m_Tail),
		m_Queue(std::move(otherQueue.m_Queue))
	{
		otherQueue.m_Capacity = 0;
		otherQueue.m_Size = 0;
		otherQueue.m_Tail = otherQueue.m_Head;
	}

	template <class T>
	Queue<T>::~Queue()
	{
		Clear();
	}

	template <class T>
	Queue<T>& Queue<T>::operator=(Queue&& otherQueue) noexcept
	{
		m_Capacity = otherQueue.m_Capacity;
		m_Size = otherQueue.m_Size;
		m_Head = otherQueue.m_Head;
		m_Tail = otherQueue.m_Tail;
		m_Queue = std::move(otherQueue.m_Queue);
		otherQueue.m_Capacity = 0;
		otherQueue.m_Size = 0;
		otherQueue.m_Tail = otherQueue.m_Head;

		return *this;
	}

	template <class T>
	void Queue<T>::Que(const T& element)
	{
		// Resize if we're over capacity
		if (m_Size + 1 >= m_Capacity)
			Resize(m_Capacity * 2);

		// Add element at Queue head
		new (&m_Queue[m_Head]) T(element);
		m_Head = (m_Head + 1) % m_Capacity;
		m_Size++;
	}

	template <class T>
	void Queue<T>::Que(T&& element)
	{
		// Resize if we're over capacity
		if (m_Size + 1 >= m_Capacity)
			Resize(m_Capacity * 2);

		// Add element at Queue head
		new (&m_Queue[m_Head]) T(std::move(element));
		m_Head = (m_Head + 1) % m_Capacity;
		m_Size++;
	}

	template <class T>
	T Queue<T>::Deque()
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
		ASSERT(m_Size > 0);
		return m_Queue[m_Tail];
	}

	template <class T>
	const T& Queue<T>::Peek() const
	{
		ASSERT(m_Size > 0);
		return m_Queue[m_Tail];
	}

	template <class T>
	T& Queue<T>::PeekEnd()
	{
		ASSERT(m_Size > 0);
		return m_Queue[(m_Head - 1) % m_Capacity];
	}

	template <class T>
	const T& Queue<T>::PeekEnd() const
	{
		ASSERT(m_Size > 0);
		return m_Queue[(m_Head - 1) % m_Capacity];
	}

	template <class T>
	u16 Queue<T>::Count() const
	{
		return m_Size;
	}

	template <class T>
	bool Queue<T>::IsEmpty() const
	{
		return m_Size == 0;
	}

	template <class T>
	void Queue<T>::Clear()
	{
		while (m_Tail != m_Head)
		{
			m_Queue[m_Tail].~T();

			m_Tail = (m_Tail + 1) % m_Capacity;
		}
		m_Size = 0;
	}

	template <class T>
	void Queue<T>::Resize(u32 newCapacity)
	{
		UniquePointer<T> newQueue = NEW_ARRAY(T, newCapacity);

		for (u32 i = 0; i < m_Size; i++)
		{
			u32 currentQueueIndex = (m_Tail + i) % m_Capacity;
			new(&newQueue[i]) T(std::move(m_Queue[currentQueueIndex]));
		}

		m_Capacity = newCapacity;
		m_Queue = std::move(newQueue);
	}
}