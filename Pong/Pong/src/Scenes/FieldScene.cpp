#include "FieldScene.h"

FieldScene::FieldScene() :
	Scene(true, true),
	m_Player(),
	m_AI()
{
	m_Player.setPosition(15.0f, 15.0f);
	m_AI.setPosition(1280.0f - 32.0f - 15.0f, 15.0f);
}

void FieldScene::Update(f32 dt)
{
	m_Player.Update(dt);
	m_AI.Update(dt);
}

void FieldScene::Draw(sf::RenderStates states) const
{
	m_Player.Draw(states);
	m_AI.Draw(states);
}

void FieldScene::ResetSceneData(void* data)
{

}