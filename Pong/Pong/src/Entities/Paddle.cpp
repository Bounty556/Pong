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
}

void Paddle::UpdateSelf(f32 dt)
{
	Soul::Controller::ButtonState upState = Soul::InputManager::GetControlState(-1, "Up").state;
	Soul::Controller::ButtonState downState = Soul::InputManager::GetControlState(-1, "Down").state;

	if (upState == Soul::Controller::Down || upState == Soul::Controller::Pressed)
		move(0.0f, -m_MoveSpeed * dt);
	if (downState == Soul::Controller::Down || downState == Soul::Controller::Pressed)
		move(0.0f, m_MoveSpeed * dt);
}

void Paddle::LateUpdateSelf(f32 dt)
{
	auto collisions = m_Collider->CheckCollisions();
	for (u32 i = 0; i < collisions.Count(); ++i)
		if (collisions[i].node->HasParentOfType("HardBoundary"))
			move(collisions[i].correctionVector);
}