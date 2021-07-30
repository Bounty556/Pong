#pragma once

#include <Defines.h>
#include <Core/Scene.h>

#include <Core/Listener.h>

#include "../Entities/Paddle.h"
#include "../Entities/Ball.h"
#include "../Entities/HardBoundary.h"

class FieldScene : public Soul::Scene
{
public:
	FieldScene();

	virtual void Update(f32 dt) override;
	virtual void LateUpdate(f32 dt) override;
	virtual void Draw(sf::RenderStates states) const override;

	virtual void ResetSceneData(void* data) override;

private:
	Paddle m_Player;
	Paddle m_AI;
	Ball m_Ball;
	HardBoundary m_TopBounds;
	HardBoundary m_BottomBounds;
	Soul::Listener m_Listener;
};