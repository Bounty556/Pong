#pragma once

#include <Defines.h>
#include <Structures/Vector.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	template <class T>
	class QuadTree
	{
	private:
		template <class T>
		struct Node
		{
			T* node;
			sf::Vector2f position;
			sf::Vector2f area;
		};

	public:
		QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxChildren);

		QuadTree(const QuadTree<T>&) = delete;
		QuadTree(QuadTree<T>&& other) noexcept;

		~QuadTree();

		QuadTree<T>& operator=(const QuadTree<T>&) = delete;
		QuadTree<T>& operator=(QuadTree<T>&& other) noexcept;

		QuadTree<T>* Insert(T* node, sf::Vector2f position, sf::Vector2f area);
		QuadTree<T>* Move(QuadTree* origin, T* node);
		void Remove(QuadTree* origin, T* node);

		Vector<T*> GetNodes(sf::Vector2f position, sf::Vector2f area);

	private:
		void AddToStorage(T* node, sf::Vector2f position, sf::Vector2f area);
		void FlattenTree();
		void SplitTree();

	private:
		u32 m_MaxChildren;
		Vector<Node<T>> m_Storage;
		QuadTree<T>* m_Children;
		sf::Vector2f m_Position;
		sf::Vector2f m_Area;
	};

	template <class T>
	QuadTree<T>::QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxChildren) :
		m_MaxChildren(maxChildren),
		m_Storage(m_MaxChildren + 1),
		m_Children(nullptr),
		m_Position(x, y),
		m_Area(width, height)
	{
	}

	template <class T>
	QuadTree<T>::QuadTree(QuadTree&& other) noexcept :
		m_MaxChildren(other.m_MaxChildren),
		m_Storage(std::move(other.m_Storage)),
		m_Children(other.m_Children),
		m_Position(other.m_Position),
		m_Area(other.m_Area)
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
		m_MaxChildren = other.m_MaxChildren;
		m_Storage = std::move(other.m_Storage);
		m_Children = other.m_Children;
		m_Position = other.m_Position;
		m_Area = other.m_Area;
		other.m_Children = nullptr;
	}

	template <class T>
	QuadTree<T>* QuadTree<T>::Insert(T* node, sf::Vector2f position, sf::Vector2f area)
	{
		// Find smallest tree this will fit in
		if (m_Children)
		{

		}
		else
		{
			AddToStorage(node, position, area);
		}
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
	void QuadTree<T>::AddToStorage(T* node, sf::Vector2f position, sf::Vector2f area)
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