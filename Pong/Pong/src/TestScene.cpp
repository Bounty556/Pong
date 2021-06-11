#include "TestScene.h"

#include <Core/Logger.h>
#include <IO/InputManager.h>
#include <Rendering/Renderer.h>
#include <UI/UIButton.h>

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
	if (Soul::InputManager::GetControlState(-1, "Right").state == Soul::Controller::Pressed)
		m_Sprite.move(0.1f * dt, 0.0f);

	m_UI.Update(dt);
}

void TestScene::Draw(sf::RenderStates states) const
{
	Soul::Renderer::Render(m_Sprite, states);
	m_UI.Draw(states);
}