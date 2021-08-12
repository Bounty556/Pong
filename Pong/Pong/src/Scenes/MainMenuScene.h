#pragma once

#include <Core/Scene.h>
#include <UI/UIContainer.h>

class MainMenuScene : public Soul::Scene
{
public:
	MainMenuScene();

	/*
	Updating and drawing the scene and the objects within
	*/
	virtual void Update(f32 dt) override;
	virtual void LateUpdate(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	Soul::UIContainer m_Container;
};