#pragma once

#include <Defines.h>

#include <Nodes/Node.h>
#include <Structures/Vector.h>

#include "CollisionChecks.h"

namespace Soul
{
	class SOULAPI IColliderNode : public Node
	{
	public:
		IColliderNode(sf::Vector2f boundingBox, const char* type);

		virtual ~IColliderNode();
		virtual Vector<CollisionInfo> CheckCollisions() const;
		virtual Vector<sf::Vector2f> GetPolygonList() const = 0;

		sf::Vector2f GetBoundingBox() const;
	protected:
		virtual CollisionInfo SpecificCollisionInfo(Node* node) const = 0;

	private:
		sf::Vector2f m_BoundingBox;
	};
}