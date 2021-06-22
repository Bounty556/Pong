#pragma once

#include <Defines.h>

#include "ICollider.h"

namespace Soul
{
	/*
	The circle collider's origin when set to (0, 0) is the center of the circle.
	Rotation does not affect the circle's orientation.
	Set position sets where the circle's origin is in world space.
	*/
	class SOULAPI CircleCollider : public ICollider
	{
	public:
		CircleCollider(f32 radius);

		CircleCollider(const CircleCollider& other);
		CircleCollider(CircleCollider&& other) noexcept;

		CircleCollider& operator=(const CircleCollider& other);
		CircleCollider& operator=(CircleCollider&& other) noexcept;

		f32 GetRadius() const;

	private:
		f32 m_Radius;
	};
}