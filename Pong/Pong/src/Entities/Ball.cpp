#include "Ball.h"

#include <Math/Random.h>
#include <Math/Vectors.h>
#include <Nodes/CircleSpriteNode.h>
#include <Rendering/Renderer.h>

Ball::Ball(f32 radius, f32 speed) :
	Node("Ball"),
	m_Collider(NEW(Soul::CircleColliderNode, radius)),
	m_Direction(Soul::Math::AngleToVector((f32)Soul::Math::Rand32(360))),
	m_Speed(speed)
{
	AddChild(m_Collider);
	AddChild(NEW(Soul::CircleSpriteNode, radius, sf::Color::White));
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
		if (collisions[i].node->HasParentOfType("HardBoundary") || collisions[i].node->HasParentOfType("Paddle"))
		{
			move(collisions[i].correctionVector);
			
			sf::Vector2f normal = Soul::Math::Normalize(collisions[i].correctionVector);

			m_Direction = Soul::Math::Reflect(m_Direction, normal);
		}
	}
}