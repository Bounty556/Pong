#include "CircleColliderNode.h"

#include <Math/Vectors.h>

namespace Soul
{
	CircleColliderNode::CircleColliderNode(sf::Vector2f boundingBox, f32 radius) :
		IColliderNode(boundingBox, "CircleColliderNode"),
		m_Radius(radius)
	{
	}

	CircleColliderNode::CircleColliderNode(CircleColliderNode&& other) noexcept :
		IColliderNode(std::move(other)),
		m_Radius(other.m_Radius)
	{
	}

	CircleColliderNode& CircleColliderNode::operator=(CircleColliderNode&& other) noexcept
	{
		IColliderNode::operator=(std::move(other));
		m_Radius = other.m_Radius;

		return *this;
	}

	Vector<sf::Vector2f> CircleColliderNode::GetPolygonList() const
	{
		Vector<sf::Vector2f> polygons(16);

		for (u32 i = 0; i < 16; ++i)
		{
			sf::Vector2f point = Math::AngleToVector(i * 22.5f) * m_Radius;
			point.x += m_Radius;
			point.y += m_Radius;
			polygons.Push(point);
		}

		return polygons;
	}

	f32 CircleColliderNode::GetRadius() const
	{
		return m_Radius;
	}
}