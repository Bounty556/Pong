#pragma once

#include <Defines.h>

#include "IColliderNode.h"

namespace Soul
{
	class SOULAPI CircleColliderNode : public IColliderNode
	{
	public:
		CircleColliderNode(sf::Vector2f boundingBox, f32 radius);

		CircleColliderNode(const CircleColliderNode&) = delete;
		CircleColliderNode(CircleColliderNode&& other) noexcept;

		CircleColliderNode& operator=(const CircleColliderNode&) = delete;
		CircleColliderNode& operator=(CircleColliderNode&& other) noexcept;

		virtual Vector<sf::Vector2f> GetPolygonList() const override;

		f32 GetRadius() const;

	private:
		f32 m_Radius;
	};
}