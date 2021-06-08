#include "TestScene.h"

#include <Core/Logger.h>

TestScene::TestScene() :
	Scene(true, true),
	m_Sprite(),
	m_Texture()
{
	if (!m_Texture.loadFromFile("res/player.png"))
		LOG_ERROR("Couldn't load from file res/player.png");

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition(50, 50);
}

void TestScene::Update(f32 dt)
{
	// Nothing to update here
}

void TestScene::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// TODO: Need to have proper drawable components that keep track of their own renderstates

	target.draw(m_Sprite, states);
}