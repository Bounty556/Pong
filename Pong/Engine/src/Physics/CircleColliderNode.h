#pragma once

#include <Defines.h>
#include <Physics/IColliderNode.h>

#include <SFML/Graphics/CircleShape.hpp>

namespace Soul
{
	class SOULAPI CircleColliderNode : public IColliderNode
	{
	public:
		CircleColliderNode(f32 radius);

		CircleColliderNode(const CircleColliderNode&) = delete;
		CircleColliderNode(CircleColliderNode&& other) noexcept;

		CircleColliderNode& operator=(const CircleColliderNode&) = delete;
		CircleColliderNode& operator=(CircleColliderNode&& other) noexcept;

		virtual Vector<sf::Vector2f> GetPolygonList() const override;

		f32 GetRadius() const;

	protected:
		virtual void DrawCollider(sf::RenderStates states) const;

	private:
		f32 m_Radius;
		sf::CircleShape m_Collider;
	};
}