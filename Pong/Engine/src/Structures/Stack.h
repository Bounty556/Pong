#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>

namespace Soul
{
	template <class T>
	class Stack
	{
	public:
		Stack(u32 capacity = 16);
		
		Stack(const Stack&) = delete;
		Stack(Stack&& otherStack) noexcept;

		~Stack();

		Stack& operator=(const Stack&) = delete;
		Stack& operator=(Stack&& otherStack) noexcept;

		const T& operator[](u32 index) const;
		T& operator[](u32 index);

		void Push(const T& element);
		void Push(T&& element);
		T Pop();
		T& Peek();
		const T& Peek() const;

		void Clear();

		u32 Count() const;
		bool IsEmpty() const;

	private:
		void Resize(u32 newCapacity);

	private:
		u32 m_Capacity;
		u32 m_Size;
		UniquePointer<T> m_Stack;
	};

	template <class T>
	Stack<T>::Stack(u32 capacity /* = 16 */) :
		m_Capacity(capacity),
		m_Size(0),
		m_Stack(NEW_ARRAY(T, capacity))
	{
	}

	template <class T>
	Stack<T>::Stack(Stack&& otherStack) noexcept :
		m_Capacity(otherStack.m_Capacity),
		m_Size(otherStack.m_Size),
		m_Stack(std::move(otherStack.m_Stack))
	{
		otherStack.m_Capacity = 0;
		otherStack.m_Size = 0;
	}

	template <class T>
	Stack<T>::~Stack()
	{
		Clear();
	}

	template <class T>
	Stack<T>& Stack<T>::operator=(Stack&& otherStack) noexcept
	{
		m_Capacity = otherStack.m_Capacity;
		m_Size = otherStack.m_Size;
		m_Stack = std::move(otherStack.m_Stack);
		otherStack.m_Capacity = 0;
		otherStack.m_Size = 0;

		return *this;
	}

	template <class T>
	const T& Stack<T>::operator[](u32 index) const
	{
		return m_Stack[index];
	}

	template <class T>
	T& Stack<T>::operator[](u32 index)
	{
		return m_Stack[index];
	}

	template <class T>
	void Stack<T>::Push(const T& element)
	{
		if (m_Size + 1 >= m_Capacity)
			Resize(m_Capacity * 2);

		new (&m_Stack[m_Size]) T(element);
		++m_Size;
	}

	template <class T>
	void Stack<T>::Push(T&& element)
	{
		if (m_Size + 1 >= m_Capacity)
			Resize(m_Capacity * 2);

		new (&m_Stack[m_Size]) T(std::move(element));
		++m_Size;
	}

	template <class T>
	T Stack<T>::Pop()
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
	void Stack<T>::Clear()
	{
		while (m_Size > 0)
			m_Stack[--m_Size].~T();
	}

	template <class T>
	u32 Stack<T>::Count() const
	{
		return m_Size;
	}

	template <class T>
	bool Stack<T>::IsEmpty() const
	{
		return m_Size == 0;
	}

	template <class T>
	void Stack<T>::Resize(u32 newCapacity)
	{
		UniquePointer<T> newStack = NEW_ARRAY(T, newCapacity);

		for (u32 i = 0; i < m_Size; i++)
			new(&newStack[i]) T(std::move(m_Stack[i]));

		m_Capacity = newCapacity;
		m_Stack = std::move(newStack);
	}
}