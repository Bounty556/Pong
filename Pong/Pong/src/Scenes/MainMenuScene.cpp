#include "MainMenuScene.h"

#include <Resources/ResourceManager.h>
#include <Resources/FontResource.h>
#include <UI/UIText.h>

MainMenuScene::MainMenuScene() :
	Scene(true, true),
	m_Container(0.0f, 0.0f, 1280.0f, 720.0f)
{
	Soul::UIPalette palette(1, sf::Color::Black);
	m_Container.SetUIPalette(palette);

	// Add title and buttons to UI
	Soul::ResourceManager::LoadResource<Soul::FontResource>("res/Fonts/font.otf", "Font");
	Soul::UIText* title = NEW(Soul::UIText, " Pong!", "Font");
	title->SetAnchor(Soul::UI::TopLeft);
	title->SetWeightingAnchor(Soul::UI::BottomLeft);
	title->SetOrigin(Soul::UI::MiddleLeft);
	title->SetAnchorWeight(0.9f);
	title->SetFontSize(72);

	m_Container.AddChild(title);
}

void MainMenuScene::Update(f32 dt)
{
	m_Container.Update(dt);
}

void MainMenuScene::LateUpdate(f32 dt)
{
}

void MainMenuScene::Draw(sf::RenderStates states) const
{
	m_Container.Draw(states);
}