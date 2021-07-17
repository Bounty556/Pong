#include "PhysicsSystem.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	QuadTree* PhysicsSystem::m_QuadTree;

	void PhysicsSystem::Initialize(f32 width, f32 height)
	{
		m_QuadTree = PARTITION(QuadTree, 0.0f, 0.0f, width, height, 8, nullptr);
	}

	void PhysicsSystem::Shutdown()
	{
		MemoryManager::FreeMemory(m_QuadTree);
	}

	void PhysicsSystem::Update(f32 dt)
	{
		m_QuadTree->Move();
	}

	void PhysicsSystem::RegisterCollider(ColliderNode* node)
	{
		m_QuadTree->Insert(node, node->GetBoundingBox());
	}

	void PhysicsSystem::UnregisterCollider(ColliderNode* node)
	{
		m_QuadTree->Remove(node);
	}

	Vector<QuadTree::QuadTreeItem*> PhysicsSystem::GetPotentialCollisions(sf::Vector2f position, sf::Vector2f area)
	{
		return m_QuadTree->GetNodes(position, area);
	}
}