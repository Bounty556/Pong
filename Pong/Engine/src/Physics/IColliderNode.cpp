#include "IColliderNode.h"

#include <Physics/PhysicsSystem.h>
#include <Rendering/Renderer.h>

namespace Soul
{
	IColliderNode::IColliderNode(sf::Vector2f boundingBox, const char* type) :
		Node(type),
		m_BoundingBox(boundingBox),
		m_IsDrawing(false)
	{
		PhysicsSystem::RegisterCollider(this);
	}

	IColliderNode::IColliderNode(IColliderNode&& other) noexcept :
		Node(std::move(other)),
		m_BoundingBox(other.m_BoundingBox),
		m_IsDrawing(other.m_IsDrawing)
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
		m_IsDrawing = other.m_IsDrawing;

		return *this;
	}

	Vector<CollisionInfo> IColliderNode::CheckCollisions() const
	{
		Vector<IColliderNode*> potentialCollisions = PhysicsSystem::GetPotentialCollisions(GetWorldPosition(), m_BoundingBox);
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

	void IColliderNode::SetDrawCollider(bool shouldDraw)
	{
		m_IsDrawing = shouldDraw;
	}

	void IColliderNode::DrawSelf(sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (m_IsDrawing)
			DrawCollider(states);
	}
}