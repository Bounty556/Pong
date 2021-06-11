#include "TestScene.h"

#include <Core/Logger.h>
#include <IO/InputManager.h>

TestScene::TestScene() :
	Scene(true, true),
	m_Sprite(),
	m_Texture()
{
	if (!m_Texture.loadFromFile("res/player.png"))
		LOG_ERROR("Couldn't load from file res/player.png");

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(50, 500);
}

void TestScene::Update(f32 dt)
{
	// Nothing to update here
	if (Soul::InputManager::GetControlState(-1, "Right").state == Soul::Controller::Pressed)
	{
		m_Sprite.move(0.1f * dt, 0.0f);
	}
}

void TestScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// TODO: Need to have proper drawable components that keep track of their own renderstates

	target.draw(m_Sprite, states);
}