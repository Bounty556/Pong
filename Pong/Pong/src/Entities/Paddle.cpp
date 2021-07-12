#include "Paddle.h"

#include <Rendering/Renderer.h>
#include <IO/InputManager.h>

Paddle::Paddle() :
	Node("Paddle"),
	m_Paddle(sf::Vector2f(32.0f, 128.0f)),
	m_MoveSpeed(1.0f)
{
	m_Paddle.setFillColor(sf::Color::White);
}

void Paddle::UpdateSelf(f32 dt)
{
	Soul::Controller::ButtonState upState = Soul::InputManager::GetControlState(-1, "Up").state;
	Soul::Controller::ButtonState downState = Soul::InputManager::GetControlState(-1, "Down").state;

	if (upState == Soul::Controller::Down || upState == Soul::Controller::Pressed)
		move(0.0f, -m_MoveSpeed * dt);
	if (downState == Soul::Controller::Down || downState == Soul::Controller::Pressed)
		move(0.0f, m_MoveSpeed * dt);

	if (getPosition().y < 15.0f)
		setPosition(getPosition().x, 15.0f);
	else if (getPosition().y > 720 - 15.0f - 128.0f)
		setPosition(getPosition().x, 720 - 15.0f - 128.0f); // TODO: variableize
}

void Paddle::DrawSelf(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Paddle, states);
}