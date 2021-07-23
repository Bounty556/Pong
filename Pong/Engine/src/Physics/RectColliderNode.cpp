#include "RectColliderNode.h"

#include <Core/String.h>
#include <Rendering/Renderer.h>

namespace Soul
{
	RectColliderNode::RectColliderNode(sf::Vector2f boundingBox) :
		IColliderNode(boundingBox, "RectColliderNode"),
		m_Collider(boundingBox)
	{
		m_Collider.setFillColor(sf::Color::Transparent);
		m_Collider.setOutlineThickness(1.0f);
		m_Collider.setOutlineColor(sf::Color::Red);
	}

	RectColliderNode::RectColliderNode(RectColliderNode&& other) noexcept :
		IColliderNode(std::move(other)),
		m_Collider(std::move(other.m_Collider))
	{
	}

	RectColliderNode& RectColliderNode::operator=(RectColliderNode&& other) noexcept
	{
		IColliderNode::operator=(std::move(other));
		m_Collider = std::move(other.m_Collider);

		return *this;
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

	void RectColliderNode::DrawCollider(sf::RenderStates states) const
	{
		Renderer::Render(m_Collider, states);
	}
}