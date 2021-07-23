#include "CircleColliderNode.h"

#include <Math/Vectors.h>
#include <Rendering/Renderer.h>

namespace Soul
{
	CircleColliderNode::CircleColliderNode(f32 radius) :
		IColliderNode(sf::Vector2f(radius * 2, radius * 2), "CircleColliderNode"),
		m_Radius(radius),
		m_Collider(radius)
	{
		m_Collider.setFillColor(sf::Color::Transparent);
		m_Collider.setOutlineThickness(1.0f);
		m_Collider.setOutlineColor(sf::Color::Red);
	}

	CircleColliderNode::CircleColliderNode(CircleColliderNode&& other) noexcept :
		IColliderNode(std::move(other)),
		m_Radius(other.m_Radius),
		m_Collider(std::move(other.m_Collider))
	{
	}

	CircleColliderNode& CircleColliderNode::operator=(CircleColliderNode&& other) noexcept
	{
		IColliderNode::operator=(std::move(other));
		m_Radius = other.m_Radius;
		m_Collider = std::move(other.m_Collider);

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

	void CircleColliderNode::DrawCollider(sf::RenderStates states) const
	{
		Renderer::Render(m_Collider, states);
	}
}