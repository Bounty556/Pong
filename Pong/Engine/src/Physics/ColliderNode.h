#pragma once

#include <Defines.h>

#include <Nodes/Node.h>
#include <Structures/Vector.h>

#include "CollisionChecks.h"

namespace Soul
{
	class SOULAPI ColliderNode : public Node
	{
	public:
		ColliderNode(sf::Vector2f boundingBox, const char* type);
		ColliderNode(sf::Vector2f boundingBox);

		virtual ~ColliderNode();

		virtual Vector<CollisionInfo> CheckCollisions();

	private:
		sf::Vector2f m_BoundingBox;
	};
}