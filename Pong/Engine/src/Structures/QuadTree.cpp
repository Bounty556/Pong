#include "QuadTree.h"

#include <Core/Logger.h>

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

	void QuadTree::Insert(IColliderNode* node)
	{
		// Find smallest tree this will fit in
		if (m_Children)
		{
			if (AABBIsInAABB(node->getPosition(), node->GetBoundingBox(), m_Children[0].m_Position, m_Children[0].m_Area))
				m_Children[0].Insert(node);
			else if (AABBIsInAABB(node->getPosition(), node->GetBoundingBox(), m_Children[1].m_Position, m_Children[1].m_Area))
				m_Children[1].Insert(node);
			else if (AABBIsInAABB(node->getPosition(), node->GetBoundingBox(), m_Children[2].m_Position, m_Children[2].m_Area))
				m_Children[2].Insert(node);
			else if (AABBIsInAABB(node->getPosition(), node->GetBoundingBox(), m_Children[3].m_Position, m_Children[3].m_Area))
				m_Children[3].Insert(node);
			else
				AddToStorage(node);
		}
		else
			AddToStorage(node);
	}

	void QuadTree::Move()
	{
		for (i32 i = m_Storage.Count() - 1; i >= 0; --i)
		{
			IColliderNode* node = m_Storage[i];
			if (!AABBIsInAABB(node->getPosition(), node->GetBoundingBox(), m_Position, m_Area))
			{
				IColliderNode* removed = Remove(node);
			
				if (node)
					m_Root->Insert(node);
			}
		}

		if (m_Children)
			for (u32 i = 0; i < 4; ++i)
				m_Children[i].Move();

		FlattenTree();
	}

	IColliderNode* QuadTree::Remove(IColliderNode* node)
	{
		IColliderNode* found = nullptr;
		for (u32 i = 0; i < m_Storage.Count(); ++i)
		{
			IColliderNode* currentNode = m_Storage[i];
			if (currentNode == node)
			{
				found = *m_Storage.RemoveAt(i);
				FlattenTree();
				return found;
			}
		}

		if (m_Children)
		{
			for (u32 i = 0; i < 4; ++i)
			{
				found = m_Children[i].Remove(node);
				if (found)
				{
					FlattenTree();
					return found;
				}
			}
		}

		return found;
	}

	Vector<IColliderNode*> QuadTree::GetNodes(sf::Vector2f position, sf::Vector2f area)
	{
		Vector<IColliderNode*> foundNodes;

		for (u32 i = 0; i < m_Storage.Count(); ++i)
			foundNodes.Push(m_Storage[i]);

		if (m_Children)
		{
			for (u32 i = 0; i < 4; ++i)
				if (AABBAABBCollision(position, area, m_Children[i].m_Position, m_Children[i].m_Area).collided)
					foundNodes.Push(m_Children[i].GetNodes(position, area));
		}

		return foundNodes;
	}

	void QuadTree::AddToStorage(IColliderNode* node)
	{
		m_Storage.Push(node);

		if (!m_Children && m_Storage.Count() > m_MaxStorage)
			SplitTree();
	}

	void QuadTree::FlattenTree()
	{
		if (m_Children)
		{
			if (!m_Children[0].m_Children && 
				!m_Children[1].m_Children &&
				!m_Children[2].m_Children &&
				!m_Children[3].m_Children)
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
			IColliderNode* toMove = Remove(m_Storage[i]);
			Insert(toMove);
		}
	}
}