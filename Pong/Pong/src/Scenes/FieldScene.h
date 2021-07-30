#pragma once

#include <Defines.h>
#include <Core/Listener.h>
#include <Core/Scene.h>
#include <Memory/UniquePointer.h>
#include <Nodes/AreaNode.h>

#include "../Entities/Paddle.h"
#include "../Entities/Ball.h"

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
	Soul::UniquePointer<Ball> m_Ball;
	Soul::AreaNode m_TopBounds;
	Soul::AreaNode m_BottomBounds;
	Soul::AreaNode m_LeftTrigger;
	Soul::AreaNode m_RightTrigger;
	Soul::Listener m_Listener;
};