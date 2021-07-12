#pragma once

#include <Defines.h>
#include <Structures/Vector.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	template <class T>
	class QuadTree
	{
	public:
		QuadTree(u32 width, u32 height);

		QuadTree(const QuadTree<T>&) = delete;
		QuadTree(QuadTree<T>&& other) noexcept;

		~QuadTree();

		QuadTree<T>& operator=(const QuadTree<T>&) = delete;
		QuadTree<T>& operator=(QuadTree<T>&& other) noexcept;

		QuadTree<T>* Insert(sf::Vector2f position, sf::Vector2f area);
		QuadTree<T>* Move(QuadTree* origin, T* node);
		void Remove(QuadTree* origin, T* node);

		Vector<T*> GetNodes(sf::Vector2f position, sf::Vector2f area);

	private:
		void FlattenTree();
		void SplitTree();

	private:
		Vector<T*> m_Storage;
		QuadTree<T>* m_Children;
	};

	template <class T>
	QuadTree<T>::QuadTree(u32 width, u32 height) :
		m_Storage(5),
		m_Children(nullptr)
	{
	}

	template <class T>
	QuadTree<T>::QuadTree(QuadTree&& other) noexcept :
		m_Storage(std::move(other.m_Storage)),
		m_Children(other.m_Children)
	{
		other.m_Children = nullptr;
	}

	template <class T>
	QuadTree<T>::~QuadTree()
	{
		if (m_Children)
			MemoryManager::FreeMemory(m_Children);
	}

	template <class T>
	QuadTree<T>& QuadTree<T>::operator=(QuadTree<T>&& other) noexcept
	{
		m_Storage = std::move(other.m_Storage);
		m_Children = other.m_Children;
		other.m_Children = nullptr;
	}

	template <class T>
	QuadTree<T>* QuadTree<T>::Insert(sf::Vector2f position, sf::Vector2f area)
	{
		// TODO:
	}

	template <class T>
	QuadTree<T>* QuadTree<T>::Move(QuadTree<T>* origin, T* node)
	{
		// TODO:
	}

	template <class T>
	void QuadTree<T>::Remove(QuadTree<T>* origin, T* node)
	{
		// TODO:
	}

	template <class T>
	Vector<T*> QuadTree<T>::GetNodes(sf::Vector2f position, sf::Vector2f area)
	{
		// TODO:
	}

	template <class T>
	void QuadTree<T>::FlattenTree()
	{
		// TODO:
	}

	template <class T>
	void QuadTree<T>::SplitTree()
	{
		// TODO:
	}
}