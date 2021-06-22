#include "Node.h"

namespace Soul
{
	Node::Node() :
		m_Parent(nullptr)
	{
	}

	Node::~Node()
	{
	}

	sf::Vector2f Node::GetWorldPosition() const
	{
		sf::Vector2f worldPos = getPosition();
		if (m_Parent)
			worldPos += m_Parent->GetWorldPosition();
		return worldPos;
	}
}