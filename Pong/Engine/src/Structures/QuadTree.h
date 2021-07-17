#pragma once

#include <Defines.h>
#include <Structures/Vector.h>
#include <Physics/CollisionChecks.h>
#include <Nodes/Node.h>

#include <SFML/System/Vector2.hpp>

class QuadTreeTests;

namespace Soul
{
	class SOULAPI QuadTree
	{
	public:
		struct QuadTreeItem
		{
			Node* node;
			sf::Vector2f area;
			QuadTree* container;
		};

	public:
		QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxStorage, QuadTree* root);

		QuadTree(const QuadTree&) = delete;
		QuadTree(QuadTree&& other) noexcept;

		~QuadTree();

		QuadTree& operator=(const QuadTree&) = delete;
		QuadTree& operator=(QuadTree&& other) noexcept;

		void Insert(Node* node, sf::Vector2f area);
		void Move(Node* node);
		QuadTreeItem Remove(Node* node);

		Vector<QuadTreeItem*> GetNodes(sf::Vector2f position, sf::Vector2f area);

	private:
		void AddToStorage(Node* node, sf::Vector2f area);
		void FlattenTree();
		void SplitTree();

	private:
		u32 m_MaxStorage; // The maximum number of nodes that can be stored in this QuadTree before attempting to split
		Vector<QuadTreeItem> m_Storage; // THe nodes in this QuadTree (not its children)
		QuadTree* m_Children; // The QuadTree's children QuadTrees
		sf::Vector2f m_Position; // The position of this QuadTree in 2D space
		sf::Vector2f m_Area; // The width and height of this QuadTree
		QuadTree* m_Root;
	};
}