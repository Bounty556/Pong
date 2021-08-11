#include "Paddle.h"

#include <IO/InputManager.h>
#include <IO/Controller.h>
#include <Nodes/RectSpriteNode.h>
#include <Rendering/Renderer.h>

Paddle::Paddle() :
	Node("Paddle"),
	m_Collider(NEW(Soul::RectColliderNode, sf::Vector2f(32.0f, 128.0f))),
	m_MoveSpeed(1.0f),
	m_Listener(),
	m_Controller(Soul::InputManager::GetController(0))
{
	AddChild(m_Collider);
	AddChild(NEW(Soul::RectSpriteNode, 32.0f, 128.0f, sf::Color::White));
	AddTag("Hard");

	m_Listener.Subscribe("ControllerConnected",
		[&](void* data)
		{
			u8* controller = (u8*)data;
			if (controller == 0)
				m_Controller = Soul::InputManager::GetController(0);
		});
	m_Listener.Subscribe("ControllerDisconnected",
		[&](void* data)
		{
			u8* controller = (u8*)data;
			if (controller == 0)
				m_Controller = nullptr;
		});
}

void Paddle::UpdateSelf(f32 dt)
{
	sf::Vector2f velocity(0.0f, 0.0f);

	if (Soul::InputManager::IsAliasDown("Up"))
		velocity.y -= m_MoveSpeed;
	if (Soul::InputManager::IsAliasDown("Down"))
		velocity.y += m_MoveSpeed;

	if (m_Controller)
		velocity.y += (m_MoveSpeed * m_Controller->GetAliasPosition("Vertical")) * 0.01f;

	SetVelocity(velocity);
}

void Paddle::LateUpdateSelf(f32 dt)
{
	auto collisions = m_Collider->CheckCollisions();
	for (u32 i = 0; i < collisions.Count(); ++i)
		if (collisions[i].node->HasTag("Hard"))
			move(collisions[i].correctionVector);
}