#pragma once

#include <Defines.h>

#include <Nodes/Node.h>
#include <Physics/RectColliderNode.h>

#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public Soul::Node
{
public:
	Paddle();

	virtual void UpdateSelf(f32 dt) override;

private:
	// Child Nodes
	Soul::RectColliderNode* m_Collider;

	f32 m_MoveSpeed;
};