#include "TestScene.h"

#include <Core/Logger.h>
#include <IO/InputManager.h>
#include <Rendering/Renderer.h>
#include <UI/UIButton.h>
#include <Core/SceneManager.h>

TestScene::TestScene() :
	Scene(true, true),
	m_Sprite(),
	m_Textures(),
	m_Fonts(),
	m_UI()
{
	m_Sprite.setTexture(*m_Textures.RequestTexture("res/player.png"));
	m_Sprite.setPosition(50, 500);

	Soul::UIButton* button1 = PARTITION(Soul::UIButton, "Start", m_Fonts, []() { LOG_DEBUG("Hello"); });
	Soul::UIButton* button2 = PARTITION(Soul::UIButton, "Quit", m_Fonts, []() { LOG_DEBUG("Quitting"); });
	button1->AddConnection(Soul::UIComponent::Up, button2);
	button1->AddConnection(Soul::UIComponent::Down, button2);
	button2->AddConnection(Soul::UIComponent::Up, button1);
	button2->AddConnection(Soul::UIComponent::Down, button1);

	button1->setPosition(500, 100);
	button2->setPosition(500, 200);

	m_UI.AddUIComponent(button1);
	m_UI.AddUIComponent(button2);
}

void TestScene::Update(f32 dt)
{
	// Nothing to update here
	if (Soul::InputManager::GetControlState(-1, "Right").state == Soul::Controller::Pressed ||
		Soul::InputManager::GetControlState(-1, "Right").state == Soul::Controller::Down)
		m_Sprite.move(0.1f * dt, 0.0f);

	m_UI.Update(dt);

	if (Soul::InputManager::GetControlState(-1, "Jump").state == Soul::Controller::Pressed)
	{
		i32* i = PARTITION(i32, 5);
		Soul::SceneManager::ResetScene(this, i);
		LOG_DEBUG("Hello");
		return;
	}
}

void TestScene::Draw(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Sprite, states);
	m_UI.Draw(states);
}

void TestScene::ResetSceneData(void* data)
{
	LOG_DEBUG("%d", *(i32*)data);
	Soul::MemoryManager::FreeMemory((i32*)data);
}