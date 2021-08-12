#include "FieldScene.h"

#include <Core/MessageBus.h>
#include <Core/SceneManager.h>
#include <IO/InputManager.h>
#include <Resources/ResourceManager.h>
#include <Resources/FontResource.h>
#include <UI/UIText.h>

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
	m_Ball(NEW(Ball, 8)),
	m_TopBounds(-5.0f, -5.0f, 1310.0f, 10.0f),
	m_BottomBounds(-5.0f, 715.0f, 1310.0f, 10.0f),
	m_LeftTrigger(-10.0f, 0.0f, 10.0f, 720.0f),
	m_RightTrigger(1280.0f, 0.0f, 10.0f, 720.0f),
	m_Listener(),
	m_UIContainer(0.0f, 0.0f, 1280.0f, 720.0f),
	m_Animation()
{
	m_UIContainer.SetCanDrag(true);

	Soul::InputManager::LoadAliases("res/Controls/defaultControls.controls");

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
			Soul::MessageBus::ClearQueue();
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
			Soul::MessageBus::ClearQueue();
			Soul::SceneManager::ResetScene(this, resetData);
		});
	m_Listener.Subscribe("StartGame",
		[&](void* data)
		{
			m_Ball->Launch(0.5f);
		});

	Soul::UIPalette clearContainer(1, sf::Color::Transparent);
	
	m_UIContainer.SetUIPalette(clearContainer);

	Soul::ResourceManager::LoadResource<Soul::FontResource>("res/Fonts/font.otf", "Font");

	Soul::UIText* text = NEW(Soul::UIText, "3", "Font");
	text->SetAnchor(Soul::UI::TopMiddle);
	text->SetAnchorWeight(0.75f);
	text->SetFontSize(48);

	Soul::UIPalette greyText(1, sf::Color(100, 100, 100));

	m_PlayerScoreText = NEW(Soul::UIText, "0", "Font");
	m_PlayerScoreText->SetAnchor(Soul::UI::MiddleLeft);
	m_PlayerScoreText->SetAnchorWeight(0.5f);
	m_PlayerScoreText->SetFontSize(98);
	m_PlayerScoreText->SetUIPalette(greyText);
	m_AIScoreText = NEW(Soul::UIText, "0", "Font");
	m_AIScoreText->SetAnchor(Soul::UI::MiddleRight);
	m_AIScoreText->SetAnchorWeight(0.5f);
	m_AIScoreText->SetFontSize(98);
	m_AIScoreText->SetUIPalette(greyText);

	m_UIContainer.AddChild(m_PlayerScoreText);
	m_UIContainer.AddChild(m_AIScoreText);
	m_UIContainer.AddChild(text);

	// We can't pass by reference here because it gets a reference to the pointer, not a reference to the object being
	// pointed to.
	m_Animation.StartFrame()
			.Lerp(1000.0f, NEW(std::function<void(f32)>, [text](f32 val) { text->SetFontSize((u32)val); }), 48.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [text]() { text->SetFontSize(48); }))
			.Call(NEW(std::function<void()>, [text]() { text->SetText("2"); }))
			.Lerp(1000.0f, NEW(std::function<void(f32)>, [text](f32 val) { text->SetFontSize((u32)val); }), 48.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [text]() { text->SetFontSize(48); }))
			.Call(NEW(std::function<void()>, [text]() { text->SetText("1"); }))
			.Lerp(1000.0f, NEW(std::function<void(f32)>, [text](f32 val) { text->SetFontSize((u32)val); }), 48.0f, 5.0f)
		.Then()
			.Call(NEW(std::function<void()>, [text]() { text->SetText(""); }))
			.Call(NEW(std::function<void()>, [text]() { Soul::MessageBus::QueueMessage("StartGame"); }));
}

void FieldScene::Update(f32 dt)
{
	m_Player.Update(dt);
	m_AI.Update(dt);
	if (m_Ball.Raw())
		m_Ball->Update(dt);
	m_UIContainer.Update(dt);
	m_Animation.Update(dt);
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
	m_UIContainer.Draw(states);
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
	m_PlayerScoreText->SetText(Soul::String::IntToString(m_PlayerScore).GetCString());
	m_AIScoreText->SetText(Soul::String::IntToString(m_AIScore).GetCString());

	LOG_INFO("Score:\n\tPlayer: %d\t\tAI: %d", m_PlayerScore, m_AIScore);

	DELETE(data);
}