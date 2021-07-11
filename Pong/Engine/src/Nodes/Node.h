#pragma once

#include <Structures/Vector.h>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace Soul
{
	class SOULAPI Node : public sf::Transformable
	{
	public:
		Node(const char* type);

		virtual ~Node();

		virtual void Update(f32 dt);
		virtual void Draw(sf::RenderStates states) const;

		void AddChild(Node* child);
		void RemoveChild(Node* child);

		sf::Transform GetGlobalTransform() const;
		
		const Vector<Node*>& GetChildren() const;
		const Node* GetParent() const;

		const char* GetType() const;
		Vector<Node*> GetChildrenOfType(const char* type) const;
		bool HasChildOfType(const char* type) const;
	
	private:
		Node* m_Parent;
		Vector<Node*> m_Children;
		const char* m_Type;
	};
}