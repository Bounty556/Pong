#pragma once

#include <Defines.h>
#include <Structures/QuadTree.h>
#include <Structures/Vector.h>

#include "IColliderNode.h"

namespace Soul
{
	class SOULAPI PhysicsSystem
	{
	public:
		PhysicsSystem() = delete;

		static bool Initialize(f32 width, f32 height);
		static void Shutdown();

		static void Update(f32 dt);

		static void RegisterCollider(IColliderNode* node);
		static void UnregisterCollider(IColliderNode* node);
		static Vector<QuadTree::QuadTreeItem*> GetPotentialCollisions(sf::Vector2f position, sf::Vector2f area);

	private:
		static QuadTree* m_QuadTree;
		static bool m_IsInitialized;
	};
}