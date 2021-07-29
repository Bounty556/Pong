#include "Node.h"

namespace Soul
{
	Node::Node(const char* type) :
		m_Children(),
		m_Parent(nullptr),
		m_Type(type),
		m_Tags(NEW(Vector<String>, 16))
	{
	}

	Node::Node(Node&& other) noexcept :
		m_Children(std::move(other.m_Children)),
		m_Parent(other.m_Parent),
		m_Type(other.m_Type),
		m_Tags(std::move(other.m_Tags))
	{
		setPosition(other.getPosition());
	}

	Node::~Node()
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			DELETE(m_Children[i]);
		m_Children.Clear();
	}

	Node& Node::operator=(Node&& other) noexcept
	{
		m_Children = std::move(other.m_Children);
		m_Parent = other.m_Parent;
		m_Type = other.m_Type;
		m_Tags = std::move(other.m_Tags);
		setPosition(other.getPosition());

		return *this;
	}

	void Node::Update(f32 dt)
	{
		UpdateSelf(dt);
		UpdateChildren(dt);
	}

	void Node::LateUpdate(f32 dt)
	{
		// Integrate
		Accelerate(m_Acceleration * dt);
		move(m_Velocity * dt);

		LateUpdateSelf(dt);
		LateUpdateChildren(dt);
	}
	
	void Node::Draw(sf::RenderStates states) const
	{
		states.transform *= getTransform();

		DrawSelf(states);
		DrawChildren(states);
	}

	void Node::AddChild(Node* child)
	{
		m_Children.Push(child);
		child->m_Parent = this;
		
		// Add any tags this child has to us, reassign child tags
		for (u32 i = 0; i < child->m_Tags->Count(); ++i)
			AddTag((*child->m_Tags)[i].GetCString());
		child->m_Tags = m_Tags;
	}

	void Node::RemoveChild(Node* child)
	{
		m_Children.Remove(child);
		child->m_Parent = nullptr;
		child->m_Tags = NEW(Vector<String>, 16);
	}

	void Node::SetVelocity(sf::Vector2f velocity)
	{
		m_Velocity = velocity;
	}

	void Node::SetVelocity(f32 xv, f32 yv)
	{
		m_Velocity = sf::Vector2f(xv, yv);
	}

	void Node::Accelerate(sf::Vector2f dv)
	{
		m_Velocity += dv;
	}

	void Node::Accelerate(f32 xdv, f32 ydv)
	{
		m_Velocity += sf::Vector2f(xdv, ydv);
	}

	void Node::SetAcceleration(sf::Vector2f accel)
	{
		m_Acceleration = accel;
	}

	void Node::SetAcceleration(f32 xa, f32 ya)
	{
		m_Acceleration = sf::Vector2f(xa, ya);
	}

	void Node::Jerk(sf::Vector2f da)
	{
		m_Acceleration += da;
	}

	void Node::Jerk(f32 xda, f32 yda)
	{
		m_Acceleration += sf::Vector2f(xda, yda);
	}

	sf::Vector2f Node::GetVelocity() const
	{
		return m_Velocity;
	}

	sf::Vector2f Node::GetAcceleration() const
	{
		return m_Acceleration;
	}

	sf::Vector2f Node::GetWorldVelocity() const
	{
		sf::Vector2f velocity = m_Velocity;

		const Node* current = this;

		while (current->m_Parent)
		{
			velocity += m_Parent->m_Velocity;
			current = current->m_Parent;
		}

		return velocity;
	}

	sf::Vector2f Node::GetWorldAcceleration() const
	{
		sf::Vector2f accel = m_Acceleration;

		const Node* current = this;

		while (current->m_Parent)
		{
			accel += m_Parent->m_Acceleration;
			current = current->m_Parent;
		}

		return accel;
	}

	sf::Vector2f Node::GetWorldPosition() const
	{
		sf::Transform transform = getTransform();
		
		const Node* current = this;

		while (current->m_Parent)
		{
			transform *= m_Parent->getTransform();
			current = current->m_Parent;
		}

		return transform * sf::Vector2f();
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
			if (m_Children[i]->GetType() == type)
				children.Push(m_Children[i]);

		return children;
	}

	bool Node::HasChildOfType(const char* type) const
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			if (m_Children[i]->GetType() == type || m_Children[i]->HasChildOfType(type))
				return true;

		return false;
	}

	bool Node::HasParentOfType(const char* type) const
	{
		return m_Parent && (m_Parent->GetType() == type || m_Parent->HasParentOfType(type));
	}

	void Node::AddTag(const char* tag)
	{
		// TODO: Maybe consider adding a Set structure
		for (u32 i = 0; i < m_Tags->Count(); ++i)
			if ((*m_Tags)[i] == tag)
				return;
		m_Tags->Push(tag);
	}

	bool Node::HasTag(const char* tag) const
	{
		for (u32 i = 0; i < m_Tags->Count(); ++i)
			if ((*m_Tags)[i] == tag)
				return true;
		return false;
	}

	void Node::RemoveTag(const char* tag)
	{
		m_Tags->Remove(tag);
	}

	void Node::UpdateSelf(f32 dt)
	{
	}

	void Node::LateUpdateSelf(f32 dt)
	{
	}

	void Node::DrawSelf(sf::RenderStates states) const
	{
	}

	void Node::UpdateChildren(f32 dt)
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->Update(dt);
	}

	void Node::LateUpdateChildren(f32 dt)
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->LateUpdate(dt);
	}

	void Node::DrawChildren(sf::RenderStates states) const
	{
		for (u32 i = 0; i < m_Children.Count(); ++i)
			m_Children[i]->Draw(states);
	}
}