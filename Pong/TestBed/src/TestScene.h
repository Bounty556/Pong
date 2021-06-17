#pragma once

#include <Core/Scene.h>

class TestScene : public Soul::Scene
{
public:
	TestScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;
};