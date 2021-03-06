#pragma once

#include <Defines.h>
#include <Memory/UniquePointer.h>
#include <Structures/Vector.h>
#include <Physics/CollisionChecks.h>
#include <Physics/IColliderNode.h>

#include <SFML/System/Vector2.hpp>

class QuadTreeTests;

namespace Soul
{
	class SOULAPI QuadTree
	{
	public:
		QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxStorage, QuadTree* root);

		QuadTree(const QuadTree&) = delete;
		QuadTree(QuadTree&& other) noexcept;

		~QuadTree();

		QuadTree& operator=(const QuadTree&) = delete;
		QuadTree& operator=(QuadTree&& other) noexcept;

		void Insert(IColliderNode* node);
		void Move();
		IColliderNode* Remove(IColliderNode* node);
		void FlattenTree();

		Vector<IColliderNode*> GetNodes(sf::Vector2f position, sf::Vector2f area);

	private:
		void AddToStorage(IColliderNode* node);
		void SplitTree();

	private:
		u32 m_MaxStorage; // The maximum number of nodes that can be stored in this QuadTree before attempting to split
		Vector<IColliderNode*> m_Storage; // The nodes in this QuadTree (not its children)
		UniquePointer<QuadTree> m_Children; // The QuadTree's children QuadTrees
		sf::Vector2f m_Position; // The position of this QuadTree in 2D space
		sf::Vector2f m_Area; // The width and height of this QuadTree
		QuadTree* m_Root;
	};
}