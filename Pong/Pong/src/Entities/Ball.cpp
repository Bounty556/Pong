#include "Ball.h"

#include <Math/Random.h>
#include <Math/Vectors.h>
#include <Nodes/CircleSpriteNode.h>
#include <Rendering/Renderer.h>

Ball::Ball(f32 radius, f32 speed) :
	Node("Ball"),
	m_Collider(NEW(Soul::CircleColliderNode, radius))
{
	AddChild(m_Collider);
	AddChild(NEW(Soul::CircleSpriteNode, radius, sf::Color::White));
	SetVelocity(Soul::Math::AngleToVector((f32)Soul::Math::Rand32(360)) * speed);
}

void Ball::LateUpdateSelf(f32 dt)
{
	auto collisions = m_Collider->CheckCollisions();
	for (u32 i = 0; i < collisions.Count(); ++i)
	{
		if (collisions[i].node->HasTag("Hard"))
		{
			sf::Vector2f normal = Soul::Math::Normalize(collisions[i].correctionVector);

			SetVelocity(Soul::Math::Reflect(GetWorldVelocity(), normal));
		}
	}
}