#include "RectColliderNode.h"

#include <Core/String.h>

namespace Soul
{
	RectColliderNode::RectColliderNode(sf::Vector2f boundingBox) :
		IColliderNode(boundingBox, "RectColliderNode")
	{
	}

	Vector<sf::Vector2f> RectColliderNode::GetPolygonList() const
	{
		Vector<sf::Vector2f> polygons(4);
		polygons.Push(sf::Vector2f(0,                  0));
		polygons.Push(sf::Vector2f(GetBoundingBox().x, 0));
		polygons.Push(sf::Vector2f(0,                  GetBoundingBox().y));
		polygons.Push(sf::Vector2f(GetBoundingBox().x, GetBoundingBox().y));

		return polygons;
	}
}