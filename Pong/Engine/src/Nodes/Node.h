#pragma once

#include <Structures/Vector.h>

#include <Memory/SharedPointer.h>
#include <Core/String.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Soul
{
	class SOULAPI Node : public sf::Transformable
	{
	public:
		Node(const char* type);

		Node(const Node&) = delete;
		Node(Node&& other) noexcept;

		virtual ~Node();

		Node& operator=(const Node&) = delete;
		Node& operator=(Node&& other) noexcept;

		void Update(f32 dt);
		void LateUpdate(f32 dt);
		void Draw(sf::RenderStates states) const;

		void AddChild(Node* child);
		void RemoveChild(Node* child);

		sf::Vector2f GetWorldPosition() const;
		
		const Vector<Node*>& GetChildren() const;
		const Node* GetParent() const;

		const char* GetType() const;
		Vector<Node*> GetChildrenOfType(const char* type) const;
		bool HasChildOfType(const char* type) const;
		bool HasParentOfType(const char* type) const;
	
		void AddTag(const char* tag);
		bool HasTag(const char* tag) const;
		void RemoveTag(const char* tag);

	protected:
		virtual void UpdateSelf(f32 dt);
		virtual void LateUpdateSelf(f32 dt);
		virtual void DrawSelf(sf::RenderStates states) const;

	private:
		void UpdateChildren(f32 dt);
		void LateUpdateChildren(f32 dt);
		void DrawChildren(sf::RenderStates states) const;

	private:
		Node* m_Parent;
		Vector<Node*> m_Children;
		const char* m_Type;
		SharedPointer<Vector<String>> m_Tags;
	};
}