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

	IColliderNode::IColliderNode(IColliderNode&& other) noexcept :
		Node(std::move(other)),
		m_BoundingBox(other.m_BoundingBox)
	{
	}

	IColliderNode::~IColliderNode()
	{
		PhysicsSystem::UnregisterCollider(this);
	}

	IColliderNode& IColliderNode::operator=(IColliderNode&& other) noexcept
	{
		Node::operator=(std::move(other));
		m_BoundingBox = other.m_BoundingBox;

		return *this;
	}

	Vector<CollisionInfo> IColliderNode::CheckCollisions() const
	{
		Vector<IColliderNode*> potentialCollisions = PhysicsSystem::GetPotentialCollisions(getPosition(), m_BoundingBox);
		Vector<CollisionInfo> actualCollisions;

		for (u32 i = 0; i < potentialCollisions.Count(); ++i)
		{
			if (potentialCollisions[i] != this)
			{
				CollisionInfo col = CalculateCollisionType(this, potentialCollisions[i]);
				if (col.collided)
				{
					col.node = potentialCollisions[i];
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
