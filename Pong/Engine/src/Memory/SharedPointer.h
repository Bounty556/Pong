#pragma once

#include <Defines.h>
#include <Memory/MemoryManager.h>
#include <Memory/ReferenceCounter.h>

namespace Soul
{
	template <class T>
	class SharedPointer
	{
	public:
		SharedPointer(T* pointer);
		SharedPointer(const SharedPointer<T>& otherPointer);
		SharedPointer(SharedPointer<T>&& otherPointer) noexcept;
		~SharedPointer();

		SharedPointer<T>& operator=(const SharedPointer<T>& otherPointer);
		SharedPointer<T>& operator=(SharedPointer<T>&& otherPointer) noexcept;
		SharedPointer<T>& operator=(T* otherPointer);

		T* operator->() const;
		T& operator*() const;
		T& operator[](u32 index) const;

		T* Raw() const;
		T* Raw();

		bool IsValid() const;

	private:
		T* m_Pointer;
		ReferenceCounter* m_References;
	};

	template <class T>
	SharedPointer<T>::SharedPointer(T* pointer) :
		m_Pointer(pointer),
		m_References(NEW(ReferenceCounter))
	{
		m_References->AddReference();
	}

	template <class T>
	SharedPointer<T>::SharedPointer(const SharedPointer<T>& otherPointer) :
		m_Pointer(otherPointer.m_Pointer),
		m_References(otherPointer.m_References)
	{
		m_References->AddReference();
	}

	template <class T>
	SharedPointer<T>::SharedPointer(SharedPointer<T>&& otherPointer) noexcept :
		m_Pointer(otherPointer.m_Pointer),
		m_References(otherPointer.m_References)
	{
		otherPointer.m_Pointer = nullptr;
		otherPointer.m_References = nullptr;
	}

	template <class T>
	SharedPointer<T>::~SharedPointer()
	{
		if (m_References && m_References->RemoveReference() == 0 && m_Pointer)
		{
			DELETE(m_References);
			DELETE(m_Pointer);
		}
	}

	template <class T>
	SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& otherPointer)
	{
		// Make sure these are separate pointers
		if (m_Pointer != otherPointer.m_Pointer)
		{
			if (m_Pointer && m_References->RemoveReference() == 0)
			{
				DELETE(m_References);
				DELETE(m_Pointer);
			}

			m_Pointer = otherPointer.m_Pointer;
			m_References = otherPointer.m_References;
			m_References->AddReference();
		}

		return *this;
	}

	template <class T>
	SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>&& otherPointer) noexcept
	{
		if (m_References && m_References->RemoveReference() == 0 && m_Pointer)
		{
			DELETE(m_References);
			DELETE(m_Pointer);
		}

		m_Pointer = otherPointer.m_Pointer;
		m_References = otherPointer.m_References;

		otherPointer.m_Pointer = nullptr;
		otherPointer.m_References = nullptr;

		return *this;
	}

	template <class T>
	SharedPointer<T>& SharedPointer<T>::operator=(T* otherPointer)
	{
		if (m_References && m_References->RemoveReference() == 0 && m_Pointer)
		{
			DELETE(m_References);
			DELETE(m_Pointer);
		}

		m_Pointer = otherPointer;
		m_References = NEW(ReferenceCounter);
		m_References->AddReference();

		return *this;
	}

	template <class T>
	T* SharedPointer<T>::operator->() const
	{
		return m_Pointer;
	}

	template <class T>
	T& SharedPointer<T>::operator*() const
	{
		return *m_Pointer;
	}

	template <class T>
	T& SharedPointer<T>::operator[](u32 index) const
	{
		return m_Pointer[index];
	}

	template <class T>
	T* SharedPointer<T>::Raw() const
	{
		return m_Pointer;
	}

	template <class T>
	T* SharedPointer<T>::Raw()
	{
		return m_Pointer;
	}

	template <class T>
	bool SharedPointer<T>::IsValid() const
	{
		return (bool)m_Pointer;
	}
}