#pragma once

#include <Structures/Vector.h>

#include <SFML/Graphics/Transformable.hpp>

namespace Soul
{
	class INode : public sf::Transformable
	{
	public:
		INode(const char* type);

		virtual ~INode();

		void AddChild(INode* child);
		void RemoveChild(INode* child);

		sf::Transform GetGlobalTransform() const;
		
		const Vector<INode*>& GetChildren() const;
		const INode* GetParent() const;

		const char* GetType() const;
		Vector<INode*> GetChildrenOfType(const char* type) const;
		bool HasChildOfType(const char* type) const;
	
	private:
		INode* m_Parent;
		Vector<INode*> m_Children;
		const char* m_Type;
	};
}