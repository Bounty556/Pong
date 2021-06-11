#pragma once

#include <Core/Scene.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <Resources/TextureManager.h>
#include <Resources/SoundManager.h>
#include <Resources/FontManager.h>

#include <SFML/Audio/Sound.hpp>

class TestScene : public Soul::Scene
{
public:
	TestScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

private:
	sf::Sprite m_Sprite;
	sf::Sprite m_Sprite2;
	sf::Sprite m_Sprite3;
	Soul::TextureManager m_Textures;
	Soul::FontManager m_Font;
	Soul::SoundManager m_Sounds;
	sf::Sound m_Sound;
};