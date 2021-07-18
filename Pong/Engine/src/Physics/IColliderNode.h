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

		IColliderNode(const IColliderNode&) = delete;
		IColliderNode(IColliderNode&& other) noexcept;

		virtual ~IColliderNode();
		
		IColliderNode& operator=(const IColliderNode&) = delete;
		IColliderNode& operator=(IColliderNode&& other) noexcept;
		
		virtual Vector<CollisionInfo> CheckCollisions() const;
		virtual Vector<sf::Vector2f> GetPolygonList() const = 0;

		sf::Vector2f GetBoundingBox() const;

	private:
		sf::Vector2f m_BoundingBox;
	};
}