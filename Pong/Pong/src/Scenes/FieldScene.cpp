#include "FieldScene.h"

#include <Core/MessageBus.h>
#include <Core/SceneManager.h>

FieldScene::FieldScene() :
	Scene(true, true),
	m_Player(),
	m_AI(),
	m_Ball(NEW(Ball, 8, 0.5f)),
	m_TopBounds(-5.0f, -5.0f, 1310.0f, 10.0f),
	m_BottomBounds(-5.0f, 715.0f, 1310.0f, 10.0f),
	m_LeftTrigger(-10.0f, 0.0f, 10.0f, 720.0f),
	m_RightTrigger(1280.0f, 0.0f, 10.0f, 720.0f),
	m_Listener()
{
	m_Player.setPosition(15.0f, 15.0f);
	m_AI.setPosition(1280.0f - 32.0f - 15.0f, 15.0f);
	m_Ball->setPosition(1280.0f / 2.0f, 720.0f / 2.0f);

	m_TopBounds.AddTag("Hard");
	m_BottomBounds.AddTag("Hard");
	m_LeftTrigger.AddTag("AI Score");
	m_RightTrigger.AddTag("Player Score");

	m_Listener.Subscribe("AIScore", 
		[&](void* data)
		{
			Soul::SceneManager::ResetScene(this, NEW(sf::Vector2f, m_Player.GetWorldPosition().y, m_AI.GetWorldPosition().y));
		});
	m_Listener.Subscribe("PlayerScore",
		[&](void* data)
		{
			Soul::SceneManager::ResetScene(this, NEW(sf::Vector2f, m_Player.GetWorldPosition().y, m_AI.GetWorldPosition().y));
		});
}

void FieldScene::Update(f32 dt)
{
	m_Player.Update(dt);
	m_AI.Update(dt);
	if (m_Ball.Raw())
		m_Ball->Update(dt);
}

void FieldScene::LateUpdate(f32 dt)
{
	m_Player.LateUpdate(dt);
	m_AI.LateUpdate(dt);
	if (m_Ball.Raw())
		m_Ball->LateUpdate(dt);
}

void FieldScene::Draw(sf::RenderStates states) const
{
	m_Player.Draw(states);
	m_AI.Draw(states);
	if (m_Ball.Raw())
		m_Ball->Draw(states);
}

void FieldScene::ResetSceneData(void* data)
{
	sf::Vector2f* posData = (sf::Vector2f*)data;

	m_Player.setPosition(m_Player.GetWorldPosition().x, posData->x);
	m_AI.setPosition(m_AI.GetWorldPosition().x, posData->y);

	DELETE(data);
}