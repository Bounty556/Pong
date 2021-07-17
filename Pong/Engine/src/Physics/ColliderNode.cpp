#include "ColliderNode.h"

namespace Soul
{
	ColliderNode::ColliderNode(sf::Vector2f boundingBox, const char* type) :
		Node(type),
		m_BoundingBox(boundingBox)
	{
		// TODO: Register
	}

	ColliderNode::ColliderNode(sf::Vector2f boundingBox) :
		Node("ColliderNode"),
		m_BoundingBox(boundingBox)
	{
		// TODO: Unregister
	}

	ColliderNode::~ColliderNode()
	{
		// TODO: Unregister
	}

	sf::Vector2f ColliderNode::GetBoundingBox() const
	{
		return m_BoundingBox;
	}

	Vector<CollisionInfo> ColliderNode::CheckCollisions() const
	{
		// TODO: Get all collisions here
	}
}
