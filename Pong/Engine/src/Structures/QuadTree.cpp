#include "QuadTree.h"

namespace Soul
{
	QuadTree::QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxStorage, QuadTree* root) :
		m_MaxStorage(maxStorage),
		m_Storage(m_MaxStorage + 1),
		m_Children(nullptr),
		m_Position(x, y),
		m_Area(width, height),
		m_Root(root)
	{
		if (!m_Root)
			m_Root = this;
	}

	QuadTree::QuadTree(QuadTree&& other) noexcept :
		m_MaxStorage(other.m_MaxStorage),
		m_Storage(std::move(other.m_Storage)),
		m_Children(other.m_Children),
		m_Position(other.m_Position),
		m_Area(other.m_Area),
		m_Root(other.m_Root)
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
		m_MaxStorage = other.m_MaxStorage;
		m_Storage = std::move(other.m_Storage);
		m_Children = other.m_Children;
		m_Position = other.m_Position;
		m_Area = other.m_Area;
		m_Root = other.m_Root;
		other.m_Children = nullptr;

		return *this;
	}

	void QuadTree::Insert(Node* node, sf::Vector2f area)
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
			AddToStorage(node, area);
	}

	void QuadTree::Move(Node* node)
	{
		// TODO: Find an alternative, this is super slow
		QuadTreeItem* found = GetNodeFromStorage(node);

		// Only move the node if it's crossed the quadTree's boundaries
		if (!AABBIsInAABB(node->getPosition(), found->area, found->container->m_Position, found->container->m_Area))
		{
			QuadTreeItem quadTreeItem = found->container->Remove(node);
			
			if (quadTreeItem.node)
				m_Root->Insert(quadTreeItem.node, quadTreeItem.area);

			m_Root->FlattenTree();
		}
	}

	QuadTree::QuadTreeItem QuadTree::Remove(Node* node)
	{
		QuadTreeItem found = {};
		for (u32 i = 0; i < m_Storage.Count(); ++i)
		{
			if (m_Storage[i].node == node)
			{
				m_Storage[i].container = nullptr;
				return *m_Storage.RemoveAt(i);
			}
		}

		if (m_Children)
		{
			for (u32 i = 0; i < 4; ++i)
			{
				found = m_Children[i].Remove(node);
				if (found.node)
					return found;
			}
		}

		return found;
	}

	Vector<QuadTree::QuadTreeItem*> QuadTree::GetNodes(sf::Vector2f position, sf::Vector2f area)
	{
		Vector<QuadTree::QuadTreeItem*> foundNodes;

		for (u32 i = 0; i < m_Storage.Count(); ++i)
			foundNodes.Push(&m_Storage[i]);

		if (m_Children)
		{
			for (u32 i = 0; i < 4; ++i)
				if (AABBAABBCollision(position, area, m_Children[i].m_Position, m_Children[i].m_Area).collided)
					foundNodes.Push(m_Children[i].GetNodes(position, area));
		}

		return foundNodes;
	}

	void QuadTree::AddToStorage(Node* node, sf::Vector2f area)
	{
		QuadTreeItem newItem = {};
		newItem.area = area;
		newItem.node = node;
		newItem.container = this;

		m_Storage.Push(newItem);

		if (!m_Children && m_Storage.Count() > m_MaxStorage)
			SplitTree();
	}

	void QuadTree::FlattenTree()
	{
		if (m_Children)
		{
			if (!m_Children[0].m_Children)
			{
				u32 allStorage = m_Storage.Count();

				for (u32 i = 0; i < 4; ++i)
					allStorage += m_Children[i].m_Storage.Count();

				if (allStorage <= u32(m_MaxStorage * 0.8f))
				{
					// Reabsorb grandchildren
					for (u32 i = 0; i < 4; ++i)
						m_Storage.Push(m_Children[i].m_Storage);

					MemoryManager::FreeMemory(m_Children);
					m_Children = nullptr;
				}
			}
			else
			{
				for (u32 i = 0; i < 4; ++i)
					m_Children[i].FlattenTree();
			}
		}
	}

	void QuadTree::SplitTree()
	{
		// Create children
		m_Children = PARTITION_ARRAY(QuadTree, 4);

		f32 halfWidth = m_Area.x * 0.5f;
		f32 halfHeight = m_Area.y * 0.5f;
		new (&m_Children[0]) QuadTree(m_Position.x,             m_Position.y,              halfWidth, halfHeight, m_MaxStorage, m_Root);
		new (&m_Children[1]) QuadTree(m_Position.x + halfWidth, m_Position.y,              halfWidth, halfHeight, m_MaxStorage, m_Root);
		new (&m_Children[2]) QuadTree(m_Position.x,             m_Position.y + halfHeight, halfWidth, halfHeight, m_MaxStorage, m_Root);
		new (&m_Children[3]) QuadTree(m_Position.x + halfWidth, m_Position.y + halfHeight, halfWidth, halfHeight, m_MaxStorage, m_Root);

		// Place children where they belong in tree
		for (i32 i = m_Storage.Count() - 1; i >= 0; --i)
		{
			QuadTreeItem toMove = Remove(m_Storage[i].node);
			Insert(toMove.node, toMove.area);
		}
	}
}