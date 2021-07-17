#pragma once

#include <Defines.h>
#include <Memory/MemoryManager.h>
#include <Memory/UniquePointer.h>
#include <Math/Functions.h>
#include <Platform/Platform.h>

namespace Soul
{
	/*
	This is to be used in place of the C Standard Template Library vectors. They should behave
	almost identically, but instead use our built-in memory arena.
	*/
	template <class T>
	class Vector
	{
	public:
		Vector(u32 capacity = 8);

		Vector(const Vector<T>&) = delete;
		Vector(Vector<T>&& otherVector) noexcept;

		Vector& operator=(const Vector<T>&) = delete;
		Vector& operator=(Vector<T>&& otherVector) noexcept;

		T& operator[](u32 index) const;

		void Push(const T& element);
		void Push(T&& element);
		void Push(const Vector<T>& elements);
		T Pop();

		/*
		Inserts an element at the given index.
		*/
		void Insert(u32 index, const T& element);
		void Insert(u32 index, T&& element);

		const T& Peek() const;

		/*
		Removes the provided element, replacing it with the final element.
		*/
		T* Remove(const T& element, bool keepOrder = false);
		T* RemoveAt(u32 index, bool keepOrder = false);
		void Clear();

		u32 Count() const;
		bool IsEmpty() const;

	private:
		void Resize(u32 newCapacity);

	private:
		u32 m_Capacity;
		u32 m_Size;
		UniquePointer<T> m_Vector;
		const u32 m_MINIMUM_CAPACITY = 8;
	};

	template <class T>
	Vector<T>::Vector(u32 capacity) :
		m_Capacity(Math::Max((i32)capacity, (i32)m_MINIMUM_CAPACITY)),
		m_Size(0),
		m_Vector(PARTITION_ARRAY(T, m_Capacity))
	{
	}

	template <class T>
	Vector<T>::Vector(Vector<T>&& otherVector) noexcept :
		m_Capacity(otherVector.m_Capacity),
		m_Size(otherVector.m_Size),
		m_Vector(std::move(otherVector.m_Vector))
	{
		otherVector.m_Capacity = 0;
		otherVector.m_Size = 0;
	}

	template <class T>
	Vector<T>& Vector<T>::operator=(Vector<T>&& otherVector) noexcept
	{
		m_Capacity = otherVector.m_Capacity;
		m_Size = otherVector.m_Size;
		m_Vector = std::move(otherVector.m_Vector);
		otherVector.m_Capacity = 0;
		otherVector.m_Size = 0;

		return *this;
	}

	template <class T>
	T& Vector<T>::operator[](u32 index) const
	{
		ASSERT(index >= 0 && index < m_Size);
		return m_Vector[index];
	}

	template <class T>
	void Vector<T>::Push(const T& element)
	{
		// Check to see if increasing our count hits our capacity.
		if (m_Size == m_Capacity)
			Resize(m_Capacity * 2);

		new (&m_Vector[m_Size++]) T(element);
	}

	template <class T>
	void Vector<T>::Push(T&& element)
	{
		// Check to see if increasing our count hits our capacity limit.
		if (m_Size == m_Capacity)
			Resize(m_Capacity * 2);

		// Put our new element at m_Count, then increase
		new (&m_Vector[m_Size++]) T(std::move(element));
	}

	template <class T>
	void Vector<T>::Push(const Vector<T>& elements)
	{
		// Check to see if increasing our count hits our capacity limit.
		while (m_Size + elements.Count() >= m_Capacity)
			Resize(m_Capacity * 2);

		for (u32 i = 0; i < elements.Count(); ++i)
			new (&m_Vector[m_Size++]) T(elements[i]); // Put our new element at m_Count, then increase
	}

	template <class T>
	T Vector<T>::Pop()
	{
		ASSERT(m_Size > 0);
	
		T pop = std::move(m_Vector[--m_Size]);
		PlatformSetMemory(&m_Vector[m_Size], 0, sizeof(T));
		return pop;
	}

	template <class T>
	void Vector<T>::Insert(u32 index, const T& element)
	{
		ASSERT(index <= m_Size);

		// Check to see if increasing our count hits our capacity limit.
		if (m_Size == m_Capacity)
			Resize(m_Capacity * 2);

		for (u32 i = m_Size; i > index; --i)
		{
			PlatformSetMemory(&m_Vector[i], 0, sizeof(T));
			new (&m_Vector[i]) T(std::move(m_Vector[i - 1]));
		}

		PlatformSetMemory(&m_Vector[index], 0, sizeof(T));
		new (&m_Vector[index]) T(element);
		++m_Size;
	}

	template <class T>
	void Vector<T>::Insert(u32 index, T&& element)
	{
		ASSERT(index <= m_Size);

		// Check to see if increasing our count hits our capacity limit.
		if (m_Size == m_Capacity)
			Resize(m_Capacity * 2);

		for (u32 i = m_Size; i > index; --i)
		{
			PlatformSetMemory(&m_Vector[i], 0, sizeof(T));
			new (&m_Vector[i]) T(std::move(m_Vector[i - 1]));
		}


		PlatformSetMemory(&m_Vector[index], 0, sizeof(T));
		new (&m_Vector[index]) T(std::move(element));
		++m_Size;
	}

	template <class T>
	const T& Vector<T>::Peek() const
	{
		ASSERT(m_Size > 0);
		return m_Vector[m_Size - 1];
	}

	template <class T>
	T* Vector<T>::Remove(const T& element, bool keepOrder /*= false*/)
	{
		for (u32 i = 0; i < m_Size; ++i)
		{
			if (m_Vector[i] == element)
			{
				if (i == m_Size - 1)
					return &m_Vector[--m_Size];
				else if (keepOrder)
				{
					// Move all contents back by 1 space
					for (u32 j = i; j < m_Size - 1; ++j)
						m_Vector[j] = std::move(m_Vector[j + 1]);
					--m_Size;

					return &m_Vector[i];
				}
				else
				{
					m_Vector[i] = std::move(m_Vector[--m_Size]);
					return &m_Vector[i];
				}
			}
		}
		
		return nullptr;
	}

	template <class T>
	T* Vector<T>::RemoveAt(u32 index, bool keepOrder /*= false*/)
	{
		ASSERT(index >= 0 && index < m_Size);

		if (index == m_Size - 1)
			return &m_Vector[--m_Size];
		else if (keepOrder)
		{
			// Move all contents back by 1 space
			for (u32 i = index; i < m_Size - 1; ++i)
				m_Vector[i] = std::move(m_Vector[i + 1]);
			--m_Size;

			return &m_Vector[index];
		}
		else
		{
			m_Vector[index] = std::move(m_Vector[--m_Size]);
			return &m_Vector[index];
		}
	}

	template <class T>
	u32 Vector<T>::Count() const
	{
		return m_Size;
	}

	template <class T>
	bool Vector<T>::IsEmpty() const
	{
		return m_Size == 0;
	}

	template <class T>
	void Vector<T>::Clear()
	{
		m_Vector = PARTITION_ARRAY(T, m_Capacity);
		m_Size = 0;
	}

	template <class T>
	void Vector<T>::Resize(u32 newCapacity)
	{
		T* newMemory = PARTITION_ARRAY(T, newCapacity);

		for (u32 i = 0; i < m_Capacity; ++i)
		{
			new (&newMemory[i]) T(std::move(m_Vector[i]));
		}

		m_Vector = newMemory;
		m_Capacity = newCapacity;
	}
}