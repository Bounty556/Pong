#pragma once

// TODO: Abstract out

namespace Soul
{
	template <class T>
	class StackIterator
	{
	public:
		StackIterator(bool isReverse, T* start);

		T& operator*() const;
		T* operator->();
		StackIterator& operator++();
		StackIterator operator++(int);
		bool operator==(const StackIterator& other) const;
		bool operator!=(const StackIterator& other) const;

	private:
		bool m_Reverse;
		T* m_Ptr;
	};

	template <class T>
	StackIterator<T>::StackIterator(bool isReverse, T* start) :
		m_Reverse(isReverse),
		m_Ptr(start)
	{
	}

	template <class T>
	T& StackIterator<T>::operator*() const
	{
		return *m_Ptr;
	}

	template <class T>
	T* StackIterator<T>::operator->()
	{
		return m_Ptr;
	}

	template <class T>
	StackIterator<T>& StackIterator<T>::operator++()
	{
		if (m_Reverse)
			m_Ptr--;
		else
			m_Ptr++;

		return *this;
	}

	template <class T>
	StackIterator<T> StackIterator<T>::operator++(int)
	{
		if (m_Reverse)
			m_Ptr--;
		else
			m_Ptr++;

		return *this;
	}

	template <class T>
	bool StackIterator<T>::operator==(const StackIterator<T>& other) const
	{
		return other.m_Ptr == m_Ptr;
	}

	template <class T>
	bool StackIterator<T>::operator!=(const StackIterator<T>& other) const
	{
		return other.m_Ptr != m_Ptr;
	}
}