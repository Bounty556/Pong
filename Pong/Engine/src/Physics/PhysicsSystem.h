#pragma once

#include <Defines.h>
#include <Structures/QuadTree.h>

namespace Soul
{
	class SOULAPI PhysicsSystem
	{
	public:
		PhysicsSystem() = delete;

		static void Initialize(f32 width, f32 height);
		static void Shutdown();

		static void Update(f32 dt);

		/*static void RegisterCollider();
		static void UnregisterCollider();
		static void CheckCollision();*/

	private:
		static QuadTree* m_QuadTree;
	};
}