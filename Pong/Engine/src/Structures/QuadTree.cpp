#include "QuadTree.h"

namespace Soul
{
	QuadTree::QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxChildren) :
		m_MaxChildren(maxChildren),
		m_Storage(m_MaxChildren + 1),
		m_Children(nullptr),
		m_Position(x, y),
		m_Area(width, height)
	{
	}

	QuadTree::QuadTree(QuadTree&& other) noexcept :
		m_MaxChildren(other.m_MaxChildren),
		m_Storage(std::move(other.m_Storage)),
		m_Children(other.m_Children),
		m_Position(other.m_Position),
		m_Area(other.m_Area)
	{
		other.m_Children = nullptr;
	}

	QuadTree::~QuadTree()
	{
		if (m_Children)
			MemoryManager::FreeMemory(m_Children);
	}

	QuadTree& QuadTree::operator=(QuadTree&& other) noexcept
	{
		m_MaxChildren = other.m_MaxChildren;
		m_Storage = std::move(other.m_Storage);
		m_Children = other.m_Children;
		m_Position = other.m_Position;
		m_Area = other.m_Area;
		other.m_Children = nullptr;

		return *this;
	}

	QuadTree* QuadTree::Insert(Node* node, sf::Vector2f area)
	{
		// Find smallest tree this will fit in
		if (m_Children)
		{
			if (AABBIsInAABB(node->getPosition(), area, m_Children[0].m_Position, m_Children[0].m_Area))
				m_Children[0].Insert(node, area);
			else if (AABBIsInAABB(node->getPosition(), area, m_Children[1].m_Position, m_Children[1].m_Area))
				m_Children[1].Insert(node, area);
			else if (AABBIsInAABB(node->getPosition(), area, m_Children[2].m_Position, m_Children[2].m_Area))
				m_Children[2].Insert(node, area);
			else if (AABBIsInAABB(node->getPosition(), area, m_Children[3].m_Position, m_Children[3].m_Area))
				m_Children[3].Insert(node, area);
			else
				AddToStorage(node, area);
		}
		else
		{
			AddToStorage(node, area);
		}

		// TODO: Figure this out
		return this;
	}

	QuadTree* QuadTree::Insert(QuadTreeItem quadTreeItem)
	{
		sf::Vector2f position = quadTreeItem.node->getPosition();
		sf::Vector2f area = quadTreeItem.area;

		// Find smallest tree this will fit in
		if (m_Children)
		{
			if (AABBIsInAABB(position, area, m_Children[0].m_Position, m_Children[0].m_Area))
				m_Children[0].Insert(quadTreeItem);
			else if (AABBIsInAABB(position, area, m_Children[1].m_Position, m_Children[1].m_Area))
				m_Children[1].Insert(quadTreeItem);
			else if (AABBIsInAABB(position, area, m_Children[2].m_Position, m_Children[2].m_Area))
				m_Children[2].Insert(quadTreeItem);
			else if (AABBIsInAABB(position, area, m_Children[3].m_Position, m_Children[3].m_Area))
				m_Children[3].Insert(quadTreeItem);
			else
				AddToStorage(quadTreeItem);
		}
		else
		{
			AddToStorage(quadTreeItem);
		}

		// TODO: Figure this out
		return this;
	}

	QuadTree* QuadTree::Move(QuadTree* origin, Node* node)
	{
		sf::Vector2f area = {};
		for (u32 i = 0; i < m_Storage.Count(); ++i)
			if (m_Storage[i].node == node)
				area = m_Storage[i].area;

		if (!AABBIsInAABB(node->getPosition(), area, m_Position, m_Area))
		{
			QuadTreeItem quadTreeItem = origin->Remove(origin, node);
			Insert(quadTreeItem);
			FlattenTree();
		}

		// TODO: Figure this out
		return this;
	}

	QuadTree::QuadTreeItem QuadTree::Remove(QuadTree* origin, Node* node)
	{
		QuadTreeItem found = {};
		for (u32 i = 0; i < m_Storage.Count(); ++i)
			if (m_Storage[i].node == node)
				return *m_Storage.RemoveAt(i);

		// TODO: Check
		return found;
	}

	Vector<Node*> QuadTree::GetNodes(sf::Vector2f position, sf::Vector2f area)
	{
		Vector<Node*> foundNodes;

		/*
		for (u32 i = 0; i < 4; ++i)
		{
			if (AABBIsInAABB(position, area, m_Children[0].m_Position, m_Children[0].m_Area))
				m_Children[0].Insert(quadTreeItem);
		}

		if (AABBIsInAABB(position, area, m_Children[0].m_Position, m_Children[0].m_Area))
			m_Children[0].Insert(quadTreeItem);
		else if (AABBIsInAABB(position, area, m_Children[1].m_Position, m_Children[1].m_Area))
			m_Children[1].Insert(quadTreeItem);
		else if (AABBIsInAABB(position, area, m_Children[2].m_Position, m_Children[2].m_Area))
			m_Children[2].Insert(quadTreeItem);
		else if (AABBIsInAABB(position, area, m_Children[3].m_Position, m_Children[3].m_Area))
			m_Children[3].Insert(quadTreeItem);*/
		return foundNodes;
	}

	void QuadTree::AddToStorage(Node* node, sf::Vector2f area)
	{
		// TODO:
	}

	void QuadTree::AddToStorage(QuadTreeItem quadTreeItem)
	{
		// TODO:
	}

	void QuadTree::FlattenTree()
	{
		// TODO:
	}

	void QuadTree::SplitTree()
	{
		// TODO:
	}
}