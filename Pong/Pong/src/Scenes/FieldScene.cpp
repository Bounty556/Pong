#include "FieldScene.h"

FieldScene::FieldScene() :
	Scene(true, true),
	m_Player(),
	m_AI(),
	m_Ball(15, 0.5f),
	m_TopBounds(-5.0f, -5.0f, 1310.0f, 10.0f),
	m_BottomBounds(-5.0f, 715.0f, 1310.0f, 10.0f)
{
	m_Player.setPosition(15.0f, 15.0f);
	m_AI.setPosition(1280.0f - 32.0f - 15.0f, 15.0f);
	m_Ball.setPosition(1280.0f / 2.0f, 720.0f / 2.0f);
}

void FieldScene::Update(f32 dt)
{
	m_Player.Update(dt);
	m_AI.Update(dt);
	m_Ball.Update(dt);
}

void FieldScene::LateUpdate(f32 dt)
{
	m_Player.LateUpdate(dt);
	m_AI.LateUpdate(dt);
	m_Ball.LateUpdate(dt);
}

void FieldScene::Draw(sf::RenderStates states) const
{
	m_Player.Draw(states);
	m_AI.Draw(states);
	m_Ball.Draw(states);
	m_TopBounds.Draw(states);
	m_BottomBounds.Draw(states);
}

void FieldScene::ResetSceneData(void* data)
{
}