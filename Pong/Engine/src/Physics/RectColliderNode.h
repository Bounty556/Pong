#pragma once

#include <Defines.h>

#include <Physics/IColliderNode.h>

#include <SFML/Graphics/RectangleShape.hpp>

namespace Soul
{
	class SOULAPI RectColliderNode : public IColliderNode
	{
	public:
		RectColliderNode(sf::Vector2f boundingBox);

		RectColliderNode(const RectColliderNode&) = delete;
		RectColliderNode(RectColliderNode&& other) noexcept;

		RectColliderNode& operator=(const RectColliderNode&) = delete;
		RectColliderNode& operator=(RectColliderNode&& other) noexcept;

		virtual Vector<sf::Vector2f> GetPolygonList() const override;

	protected:
		virtual void DrawCollider(sf::RenderStates states) const override;

	private:
		sf::RectangleShape m_Collider;
	};
}