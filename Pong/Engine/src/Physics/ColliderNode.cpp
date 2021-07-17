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

	Vector<CollisionInfo> ColliderNode::CheckCollisions()
	{
		// TODO: Get all collisions here
	}
}
