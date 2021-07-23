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

		void SetDrawCollider(bool shouldDraw);
		virtual void DrawSelf(sf::RenderStates states) const override;

	protected:
		virtual void DrawCollider(sf::RenderStates states) const = 0;

	private:
		sf::Vector2f m_BoundingBox;
		bool m_IsDrawing;
	};
}