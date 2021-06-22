#pragma once

#include <Defines.h>

#include "ICollider.h"

namespace Soul
{
	class SOULAPI RectangleCollider : public ICollider
	{
	public:
		RectangleCollider(f32 width, f32 height);

		RectangleCollider(const RectangleCollider& other);
		RectangleCollider(RectangleCollider&& other) noexcept;

		RectangleCollider& operator=(const RectangleCollider& other);
		RectangleCollider& operator=(RectangleCollider&& other) noexcept;

		f32 GetWidth() const;
		f32 GetHeight() const;

	private:
		f32 m_Width;
		f32 m_Height;
	};
}