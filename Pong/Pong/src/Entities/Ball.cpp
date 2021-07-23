#include "Ball.h"

#include <Math/Random.h>
#include <Math/Vectors.h>
#include <Rendering/Renderer.h>

Ball::Ball(f32 radius, f32 speed) :
	Node("Ball"),
	m_Collider(NEW(Soul::CircleColliderNode, radius)),
	m_Ball(radius),
	m_Direction(Soul::Math::AngleToVector((f32)Soul::Math::Rand32(360))),
	m_Speed(speed)
{
	AddChild(m_Collider);
	m_Ball.setFillColor(sf::Color::White);
}

void Ball::UpdateSelf(f32 dt)
{
	move(m_Direction * m_Speed * dt);
}

void Ball::LateUpdateSelf(f32 dt)
{
	auto collisions = m_Collider->CheckCollisions();
	for (u32 i = 0; i < collisions.Count(); ++i)
	{
		if (collisions[i].node->HasParentOfType("Paddle"))
		{
			LOG_INFO("WOOT!");
			break;
		}
	}
}

void Ball::DrawSelf(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Ball, states);
}