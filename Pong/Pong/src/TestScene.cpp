#include "TestScene.h"

#include <Core/Logger.h>
#include <IO/InputManager.h>

TestScene::TestScene() :
	Scene(true, true),
	m_Sprite(),
	m_Sprite2(),
	m_Sprite3(),
	m_Textures(),
	m_Font(),
	m_Sounds(),
	m_Sound()
{
	m_Sprite.setTexture(*m_Textures.RequestTexture("res/player.png"));
	m_Sprite2.setTexture(*m_Textures.RequestTexture("res/player.png"));
	m_Sprite3.setTexture(*m_Textures.RequestTexture("res/player.png"));
	m_Sprite.setPosition(50, 500);
	m_Sprite2.setPosition(50, 550);
	m_Sprite3.setPosition(50, 600);

	LOG_DEBUG("%d", m_Textures.Count());

	m_Sound.setBuffer(*m_Sounds.RequestSound("res/sound.ogg"));
	m_Sound.play();
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
	target.draw(m_Sprite2, states);
	target.draw(m_Sprite3, states);
}