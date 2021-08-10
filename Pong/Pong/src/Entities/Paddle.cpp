#include "Paddle.h"

#include <IO/InputManager.h>
#include <Nodes/RectSpriteNode.h>
#include <Rendering/Renderer.h>

Paddle::Paddle() :
	Node("Paddle"),
	m_Collider(NEW(Soul::RectColliderNode, sf::Vector2f(32.0f, 128.0f))),
	m_MoveSpeed(1.0f)
{
	AddChild(m_Collider);
	AddChild(NEW(Soul::RectSpriteNode, 32.0f, 128.0f, sf::Color::White));
	AddTag("Hard");
}

void Paddle::UpdateSelf(f32 dt)
{
	sf::Vector2f velocity(0.0f, 0.0f);

	if (Soul::InputManager::IsAliasDown("Up"))
		velocity.y -= m_MoveSpeed;
	if (Soul::InputManager::IsAliasDown("Down"))
		velocity.y += m_MoveSpeed;

	SetVelocity(velocity);
}

void Paddle::LateUpdateSelf(f32 dt)
{
	auto collisions = m_Collider->CheckCollisions();
	for (u32 i = 0; i < collisions.Count(); ++i)
		if (collisions[i].node->HasTag("Hard"))
			move(collisions[i].correctionVector);
}