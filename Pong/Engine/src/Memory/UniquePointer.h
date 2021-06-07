#pragma once

#include <Defines.h>
#include <Memory/MemoryManager.h>

// TODO: Allow UniquePointers to be able to be instantiated with no value, and just be "invalid".

namespace Soul
{
	template <class T>
	class UniquePointer
	{
	public:
		UniquePointer(T* pointer);
		UniquePointer(const UniquePointer<T>&) = delete;
		UniquePointer(UniquePointer<T>&& otherPointer);
		~UniquePointer();

		UniquePointer<T>& operator=(const UniquePointer<T>&) = delete;
		UniquePointer<T>& operator=(UniquePointer<T>&& otherPointer);
		UniquePointer<T>& operator=(T* otherPointer);

		T* operator->() const;
		T& operator*() const;
		T& operator[](unsigned int index) const;

		T* Raw() const;

	private:
		T* m_Pointer;
	};

	template <class T>
	UniquePointer<T>::UniquePointer(T* pointer) :
		m_Pointer(pointer)
	{
	}

	template <class T>
	UniquePointer<T>::UniquePointer(UniquePointer<T>&& otherPointer) :
		m_Pointer(otherPointer.m_Pointer)
	{
		otherPointer.m_Pointer = nullptr;
	}

	template <class T>
	UniquePointer<T>::~UniquePointer()
	{
		if (m_Pointer)
			MemoryManager::FreeMemory(m_Pointer);
	}

	template <class T>
	UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer<T>&& otherPointer)
	{
		if (m_Pointer)
			MemoryManager::FreeMemory(m_Pointer);

		m_Pointer = otherPointer.m_Pointer;
		otherPointer.m_Pointer = nullptr;

		return *this;
	}

	template <class T>
	UniquePointer<T>& UniquePointer<T>::operator=(T* otherPointer)
	{
		if (m_Pointer)
			MemoryManager::FreeMemory(m_Pointer);

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
	T& UniquePointer<T>::operator[](unsigned int index) const
	{
		return m_Pointer[index];
	}

	template <class T>
	T* UniquePointer<T>::Raw() const
	{
		return m_Pointer;
	}
}