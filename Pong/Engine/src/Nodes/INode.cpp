#include "INode.h"

namespace Soul
{
	INode::INode(const char* type) :
		m_Children(),
		m_Parent(nullptr),
		m_Type(type)
	{
	}

	INode::~INode()
	{
	}

	void INode::Update(f32 dt)
	{
	}
	
	void INode::Draw(sf::RenderStates states) const
	{
	}

	void INode::AddChild(INode* child)
	{
		m_Children.Push(child);
		child->m_Parent = this;
	}

	void INode::RemoveChild(INode* child)
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

	sf::Transform INode::GetGlobalTransform() const
	{
		sf::Transform transform;
		if (m_Parent)
			transform = m_Parent->GetGlobalTransform();
		transform *= getTransform();
		return transform;
	}

	const Vector<INode*>& INode::GetChildren() const
	{
		return m_Children;
	}

	const INode* INode::GetParent() const
	{
		return m_Parent;
	}

	const char* INode::GetType() const
	{
		return m_Type;
	}

	Vector<INode*> INode::GetChildrenOfType(const char* type) const
	{
		Vector<INode*> children;

		for (u32 i = 0; i < m_Children.Count(); ++i)
		{
			if (m_Children[i]->GetType() == type)
				children.Push(m_Children[i]);
		}

		return children;
	}

	bool INode::HasChildOfType(const char* type) const
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
		{
			if (m_Children[i]->GetType() == type)
				return true;
		}

		return false;
	}
}