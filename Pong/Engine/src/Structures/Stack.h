#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>
#include <Structures/Iterators/StackIterator.h>

// TODO: There may be some issues with storing objects in here that have non-copyable data, or with very deep data stored in them. May need to investigate and some more testing with this class.

namespace Soul
{
	template <class T>
	class Stack
	{
	public:
		Stack(u16 capacity = 16);
		Stack(const Stack&) = delete;
		Stack(Stack&& otherStack);

		Stack& operator=(const Stack&) = delete;
		Stack& operator=(Stack&& otherStack);

		void Push(const T& element);
		void Push(T&& element);
		T&& Pop();
		T& Peek();
		const T& Peek() const;

		StackIterator<T> Begin();
		StackIterator<T> End();

		StackIterator<T> RBegin();
		StackIterator<T> REnd();

		u16 Count() const;
		bool IsEmpty() const;

	private:
		u16 m_Capacity;
		u16 m_Size;
		UniquePointer<T> m_Stack;
	};

	template <class T>
	Stack<T>::Stack(u16 capacity /* = 16 */) :
		m_Capacity(capacity),
		m_Size(0),
		m_Stack(PARTITION_ARRAY(T, capacity))
	{
	}

	template <class T>
	Stack<T>::Stack(Stack&& otherStack) :
		m_Capacity(otherStack.m_Capacity),
		m_Size(otherStack.m_Size),
		m_Stack(std::move(otherStack.m_Stack))
	{
		otherStack.m_Capacity = 0;
		otherStack.m_Size = 0;
	}

	template <class T>
	Stack<T>& Stack<T>::operator=(Stack&& otherStack)
	{
		m_Capacity = otherStack.m_Capacity;
		m_Size = otherStack.m_Size;
		m_Stack = std::move(otherStack.m_Stack);
		otherStack.m_Capacity = 0;
		otherStack.m_Size = 0;
	}

	template <class T>
	void Stack<T>::Push(const T& element)
	{
		new (&m_Stack[m_Size]) T(element);
		++m_Size;
	}

	template <class T>
	void Stack<T>::Push(T&& element)
	{
		new (&m_Stack[m_Size]) T(std::move(element));
		++m_Size;
	}

	template <class T>
	T&& Stack<T>::Pop()
	{
		ASSERT(m_Size > 0);
		return std::move(m_Stack[--m_Size]);
	}

	template <class T>
	T& Stack<T>::Peek()
	{
		return m_Stack[m_Size - 1];
	}

	template <class T>
	const T& Stack<T>::Peek() const
	{
		return m_Stack[m_Size - 1];
	}

	template <class T>
	StackIterator<T> Stack<T>::Begin()
	{
		return StackIterator<T>(false, m_Stack.Raw());
	}

	template <class T>
	StackIterator<T> Stack<T>::End()
	{
		if (m_Size > 0)
			return StackIterator<T>(false, &m_Stack[m_Size]);
		else
			return StackIterator<T>(false, m_Stack.Raw());
	}

	template <class T>
	StackIterator<T> Stack<T>::RBegin()
	{
		if (m_Size > 0)
			return StackIterator<T>(true, &m_Stack[m_Size - 1]);
		else
			return StackIterator<T>(true, m_Stack.Raw());
	}

	template <class T>
	StackIterator<T> Stack<T>::REnd()
	{
		return StackIterator<T>(true, m_Stack.Raw() - 1);
	}

	template <class T>
	u16 Stack<T>::Count() const
	{
		return m_Size;
	}

	template <class T>
	bool Stack<T>::IsEmpty() const
	{
		return m_Size == 0;
	}
}