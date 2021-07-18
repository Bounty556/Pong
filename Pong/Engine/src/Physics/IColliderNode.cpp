#include "IColliderNode.h"

#include "PhysicsSystem.h"

namespace Soul
{
	IColliderNode::IColliderNode(sf::Vector2f boundingBox, const char* type) :
		Node(type),
		m_BoundingBox(boundingBox)
	{
		PhysicsSystem::RegisterCollider(this);
	}

	IColliderNode::~IColliderNode()
	{
		PhysicsSystem::UnregisterCollider(this);
	}

	Vector<CollisionInfo> IColliderNode::CheckCollisions() const
	{
		Vector<QuadTree::QuadTreeItem*> potentialCollisions = PhysicsSystem::GetPotentialCollisions(getPosition(), m_BoundingBox);
		Vector<CollisionInfo> actualCollisions;

		for (u32 i = 0; i < potentialCollisions.Count(); ++i)
		{
			if (potentialCollisions[i]->node != this)
			{
				CollisionInfo col = CalculateCollisionType((Node*)this, potentialCollisions[i]->node);
				if (col.collided)
				{
					col.node = potentialCollisions[i]->node;
					actualCollisions.Push(col);
				}
			}
		}

		return actualCollisions;
	}

	sf::Vector2f IColliderNode::GetBoundingBox() const
	{
		return m_BoundingBox;
	}
}
