#include "Ball.h"

#include <Math/Random.h>
#include <Math/Vectors.h>
#include <Rendering/Renderer.h>

Ball::Ball(f32 radius, f32 speed) :
	Node("Ball"),
	m_Ball(radius),
	m_Direction(Soul::Math::AngleToVector((f32)Soul::Math::Rand32(360))),
	m_Speed(speed)
{
}

void Ball::UpdateSelf(f32 dt)
{
	move(m_Direction * m_Speed * dt);
}

void Ball::DrawSelf(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Ball, states);
}