#include "FieldScene.h"

#include <Core/MessageBus.h>
#include <Core/SceneManager.h>

struct ResetData
{
	u8 playerScore;
	u8 aiScore;
	f32 playerY;
	f32 aiY;
};

FieldScene::FieldScene() :
	Scene(true, true),
	m_Player(),
	m_AI(),
	m_PlayerScore(0),
	m_AIScore(0),
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
			ResetData* resetData = NEW(ResetData);
			resetData->playerScore = m_PlayerScore;
			resetData->aiScore = m_AIScore + 1;
			resetData->playerY = m_Player.GetWorldPosition().y;
			resetData->aiY = m_AI.GetWorldPosition().y;
			Soul::SceneManager::ResetScene(this, resetData);
		});
	m_Listener.Subscribe("PlayerScore",
		[&](void* data)
		{
			ResetData* resetData = NEW(ResetData);
			resetData->playerScore = m_PlayerScore + 1;
			resetData->aiScore = m_AIScore;
			resetData->playerY = m_Player.GetWorldPosition().y;
			resetData->aiY = m_AI.GetWorldPosition().y;
			Soul::SceneManager::ResetScene(this, resetData);
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
	ResetData* resetData = (ResetData*)data;

	m_Player.setPosition(m_Player.GetWorldPosition().x, resetData->playerY);
	m_AI.setPosition(m_AI.GetWorldPosition().x, resetData->aiY);
	m_PlayerScore = resetData->playerScore;
	m_AIScore = resetData->aiScore;

	LOG_INFO("Score:\n\tPlayer: %d\t\tAI: %d", m_PlayerScore, m_AIScore);

	DELETE(data);
}