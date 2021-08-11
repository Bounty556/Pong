#pragma once

#include <Defines.h>

#include <Core/Listener.h>
#include <IO/Controller.h>
#include <Nodes/Node.h>
#include <Physics/RectColliderNode.h>

#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public Soul::Node
{
public:
	Paddle();

	virtual void UpdateSelf(f32 dt) override;
	virtual void LateUpdateSelf(f32 dt) override;

private:
	// Child Nodes
	Soul::RectColliderNode* m_Collider;

	Soul::Listener m_Listener;
	Soul::Controller* m_Controller;
	f32 m_MoveSpeed;
};