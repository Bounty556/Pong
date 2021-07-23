#include "HardBoundary.h"

#include <Physics/RectColliderNode.h>

HardBoundary::HardBoundary(f32 x, f32 y, f32 width, f32 height) :
	Node("HardBoundary")
{
	AddChild(NEW(Soul::RectColliderNode, sf::Vector2f(width, height)));
	setPosition(x, y);
}