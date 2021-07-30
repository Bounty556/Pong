#include "AreaNode.h"

#include <Physics/RectColliderNode.h>

namespace Soul
{
	AreaNode::AreaNode(f32 x, f32 y, f32 width, f32 height) :
		Node("AreaNode")
	{
		Soul::RectColliderNode* node = NEW(Soul::RectColliderNode, sf::Vector2f(width, height));
		AddChild(node);
		setPosition(x, y);
	}
}