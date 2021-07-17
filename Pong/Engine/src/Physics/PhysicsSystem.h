#pragma once

#include <Defines.h>
#include <Structures/QuadTree.h>
#include <Structures/Vector.h>

#include "ColliderNode.h"

namespace Soul
{
	class SOULAPI PhysicsSystem
	{
	public:
		PhysicsSystem() = delete;

		static void Initialize(f32 width, f32 height);
		static void Shutdown();

		static void Update(f32 dt);

		static void RegisterCollider(ColliderNode* node);
		static void UnregisterCollider(ColliderNode* node);
		static Vector<QuadTree::QuadTreeItem*> GetPotentialCollisions(sf::Vector2f position, sf::Vector2f area);

	private:
		static QuadTree* m_QuadTree;
	};
}