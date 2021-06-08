#pragma once

#include <Core/Scene.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class TestScene : public Soul::Scene
{
public:
	TestScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};