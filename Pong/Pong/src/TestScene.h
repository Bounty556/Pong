#pragma once

#include <Core/Scene.h>

#include <SFML/Graphics/Sprite.hpp>
#include <Resources/TextureManager.h>
#include <Resources/FontManager.h>
#include <UI/UIContainer.h>

class TestScene : public Soul::Scene
{
public:
	TestScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	sf::Sprite m_Sprite;
	Soul::TextureManager m_Textures;
	Soul::FontManager m_Fonts;
	Soul::UIContainer m_UI;
};