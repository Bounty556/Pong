#include "CircleCollider.h"

namespace Soul
{
	CircleCollider::CircleCollider(f32 radius) :
		ICollider(),
		m_Radius(radius)
	{
	}

	CircleCollider::CircleCollider(const CircleCollider& other):
		m_Radius(other.m_Radius)
	{
		setOrigin(other.getOrigin());
		setRotation(other.getRotation());
		setPosition(other.getPosition());
		setScale(other.getScale());
	}

	CircleCollider::CircleCollider(CircleCollider&& other) noexcept :
		m_Radius(other.m_Radius)
	{
		setOrigin(other.getOrigin());
		setRotation(other.getRotation());
		setPosition(other.getPosition());
		setScale(other.getScale());
	}

	CircleCollider& CircleCollider::operator=(const CircleCollider& other)
	{
		m_Radius = other.m_Radius;
		setOrigin(other.getOrigin());
		setRotation(other.getRotation());
		setPosition(other.getPosition());
		setScale(other.getScale());
	}

	CircleCollider& CircleCollider::operator=(CircleCollider&& other) noexcept
	{
		m_Radius = other.m_Radius;
		setOrigin(other.getOrigin());
		setRotation(other.getRotation());
		setPosition(other.getPosition());
		setScale(other.getScale());
	}

	f32 CircleCollider::GetRadius() const
	{
		return m_Radius;
	}
}