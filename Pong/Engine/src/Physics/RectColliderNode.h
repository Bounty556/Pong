#pragma once

#include <Defines.h>

#include "IColliderNode.h"

namespace Soul
{
	class SOULAPI RectColliderNode : public IColliderNode
	{
	public:
		RectColliderNode(sf::Vector2f boundingBox);

		virtual Vector<sf::Vector2f> GetPolygonList() const override;
	};
}