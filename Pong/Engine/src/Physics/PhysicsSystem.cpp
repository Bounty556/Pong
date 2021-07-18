#include "PhysicsSystem.h"

#include <Memory/MemoryManager.h>

namespace Soul
{
	QuadTree* PhysicsSystem::m_QuadTree;
	bool PhysicsSystem::m_IsInitialized = false;

	bool PhysicsSystem::Initialize(f32 width, f32 height)
	{
		m_IsInitialized = true;
		m_QuadTree = PARTITION(QuadTree, 0.0f, 0.0f, width, height, 8, nullptr);
		return true;
	}

	void PhysicsSystem::Shutdown()
	{
		ASSERT(m_IsInitialized);
		MemoryManager::FreeMemory(m_QuadTree);
	}

	void PhysicsSystem::Update(f32 dt)
	{
		ASSERT(m_IsInitialized);
		m_QuadTree->Move();
	}

	void PhysicsSystem::RegisterCollider(IColliderNode* node)
	{
		ASSERT(m_IsInitialized);
		m_QuadTree->Insert(node, node->GetBoundingBox());
	}

	void PhysicsSystem::UnregisterCollider(IColliderNode* node)
	{
		ASSERT(m_IsInitialized);
		m_QuadTree->Remove(node);
	}

	Vector<QuadTree::QuadTreeItem*> PhysicsSystem::GetPotentialCollisions(sf::Vector2f position, sf::Vector2f area)
	{
		ASSERT(m_IsInitialized);
		return m_QuadTree->GetNodes(position, area);
	}
}