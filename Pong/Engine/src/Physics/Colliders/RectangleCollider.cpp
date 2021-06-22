#include "RectangleCollider.h"

namespace Soul
{
	RectangleCollider::RectangleCollider(f32 width, f32 height) :
		ICollider(),
		m_Width(width),
		m_Height(height)
	{
	}

	RectangleCollider::RectangleCollider(const RectangleCollider& other) :
		ICollider(),
		m_Width(other.m_Width),
		m_Height(other.m_Height)
	{
	}

	RectangleCollider::RectangleCollider(RectangleCollider&& other) noexcept :
		ICollider(),
		m_Width(other.m_Width),
		m_Height(other.m_Height)
	{
	}

	RectangleCollider& RectangleCollider::operator=(const RectangleCollider& other)
	{
		m_Width = other.m_Width;
		m_Height = other.m_Height;
	}

	RectangleCollider& RectangleCollider::operator=(RectangleCollider&& other) noexcept
	{
		m_Width = other.m_Width;
		m_Height = other.m_Height;
	}

	f32 RectangleCollider::GetWidth() const
	{
		return m_Width;
	}

	f32 RectangleCollider::GetHeight() const
	{
		return m_Height;
	}
}