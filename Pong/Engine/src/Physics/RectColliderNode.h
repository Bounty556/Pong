#pragma once

#include <Defines.h>

#include "IColliderNode.h"

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
	};
}