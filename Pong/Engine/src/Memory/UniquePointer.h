#pragma once

#include <Defines.h>
#include <Memory/MemoryManager.h>


namespace Soul
{
	template <class T>
	class UniquePointer
	{
	public:
		UniquePointer(T* pointer);
		UniquePointer(const UniquePointer<T>&) = delete;
		UniquePointer(UniquePointer<T>&& otherPointer) noexcept;
		~UniquePointer();

		UniquePointer<T>& operator=(const UniquePointer<T>&) = delete;
		UniquePointer<T>& operator=(UniquePointer<T>&& otherPointer) noexcept;
		UniquePointer<T>& operator=(T* otherPointer);

		T* operator->() const;
		T& operator*() const;
		T& operator[](u32 index) const;

		T* Raw() const;
		T* Raw();

	private:
		T* m_Pointer;
	};

	template <class T>
	UniquePointer<T>::UniquePointer(T* pointer) :
		m_Pointer(pointer)
	{
	}

	template <class T>
	UniquePointer<T>::UniquePointer(UniquePointer<T>&& otherPointer) noexcept :
		m_Pointer(otherPointer.m_Pointer)
	{
		otherPointer.m_Pointer = nullptr;
	}

	template <class T>
	UniquePointer<T>::~UniquePointer()
	{
		if (m_Pointer)
			DELETE(m_Pointer);
	}

	template <class T>
	UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& otherPointer) noexcept
	{
		if (m_Pointer)
			DELETE(m_Pointer);

		m_Pointer = otherPointer.m_Pointer;
		otherPointer.m_Pointer = nullptr;

		return *this;
	}

	template <class T>
	UniquePointer<T>& UniquePointer<T>::operator=(T* otherPointer)
	{
		if (m_Pointer)
			DELETE(m_Pointer);

		m_Pointer = otherPointer;

		return *this;
	}

	template <class T>
	T* UniquePointer<T>::operator->() const
	{
		return m_Pointer;
	}

	template <class T>
	T& UniquePointer<T>::operator*() const
	{
		return *m_Pointer;
	}

	template <class T>
	T& UniquePointer<T>::operator[](u32 index) const
	{
		return m_Pointer[index];
	}

	template <class T>
	T* UniquePointer<T>::Raw() const
	{
		return m_Pointer;
	}

	template <class T>
	T* UniquePointer<T>::Raw()
	{
		return m_Pointer;
	}
}