#include "Node.h"

namespace Soul
{
	Node::Node(const char* type) :
		m_Children(),
		m_Parent(nullptr),
		m_Type(type)
	{
	}

	Node::~Node()
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			MemoryManager::FreeMemory(m_Children[i]);
		m_Children.Clear();
	}

	void Node::Update(f32 dt)
	{
	}
	
	void Node::Draw(sf::RenderStates states) const
	{
	}

	void Node::AddChild(Node* child)
	{
		m_Children.Push(child);
		child->m_Parent = this;
	}

	void Node::RemoveChild(Node* child)
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
		{
			if (m_Children[i] == child)
			{
				m_Children.Remove(i);
				child->m_Parent = nullptr;
				break;
			}
		}
	}

	sf::Transform Node::GetGlobalTransform() const
	{
		sf::Transform transform;
		if (m_Parent)
			transform = m_Parent->GetGlobalTransform();
		transform *= getTransform();
		return transform;
	}

	const Vector<Node*>& Node::GetChildren() const
	{
		return m_Children;
	}

	const Node* Node::GetParent() const
	{
		return m_Parent;
	}

	const char* Node::GetType() const
	{
		return m_Type;
	}

	Vector<Node*> Node::GetChildrenOfType(const char* type) const
	{
		Vector<Node*> children;

		for (u32 i = 0; i < m_Children.Count(); ++i)
		{
			if (m_Children[i]->GetType() == type)
				children.Push(m_Children[i]);
		}

		return children;
	}

	bool Node::HasChildOfType(const char* type) const
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
		{
			if (m_Children[i]->GetType() == type)
				return true;
		}

		return false;
	}
}