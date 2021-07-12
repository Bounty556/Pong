#pragma once

#include <Defines.h>
#include <Core/Scene.h>

#include "../Entities/Paddle.h"
#include "../Entities/Ball.h"

class FieldScene : public Soul::Scene
{
public:
	FieldScene();

	virtual void Update(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

	virtual void ResetSceneData(void* data) override;

private:
	Paddle m_Player;
	Paddle m_AI;
	Ball m_Ball;
};