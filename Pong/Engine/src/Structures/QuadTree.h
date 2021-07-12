#pragma once

#include <Defines.h>
#include <Structures/Vector.h>
#include <Physics/CollisionChecks.h>
#include <Nodes/Node.h>

#include <SFML/System/Vector2.hpp>

namespace Soul
{
	class QuadTree
	{
	private:
		struct QuadTreeItem
		{
			Node* node;
			sf::Vector2f area;
		};

	public:
		QuadTree(f32 x, f32 y, f32 width, f32 height, u32 maxChildren);

		QuadTree(const QuadTree&) = delete;
		QuadTree(QuadTree&& other) noexcept;

		~QuadTree();

		QuadTree& operator=(const QuadTree&) = delete;
		QuadTree& operator=(QuadTree&& other) noexcept;

		QuadTree* Insert(Node* node, sf::Vector2f area);
		QuadTree* Insert(QuadTreeItem quadTreeItem);
		QuadTree* Move(QuadTree* origin, Node* node);
		QuadTreeItem Remove(QuadTree* origin, Node* node);

		Vector<Node*> GetNodes(sf::Vector2f position, sf::Vector2f area);

	private:
		void AddToStorage(Node* node, sf::Vector2f area);
		void AddToStorage(QuadTreeItem quadTreeItem);
		void FlattenTree();
		void SplitTree();

	private:
		u32 m_MaxChildren;
		Vector<QuadTreeItem> m_Storage;
		QuadTree* m_Children;
		sf::Vector2f m_Position;
		sf::Vector2f m_Area;
	};
}