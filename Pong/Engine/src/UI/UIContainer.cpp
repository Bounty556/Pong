#include "UIContainer.h"

#include <IO/InputManager.h>

namespace Soul
{
	UIContainer::UIContainer() :
		m_Components(),
		m_HoveredComponent(nullptr)
	{
	}

	UIContainer::~UIContainer()
	{
		for (unsigned int i = 0; i < m_Components.Count(); ++i)
			MemoryManager::FreeMemory(m_Components[i]);
	}

	void UIContainer::AddUIComponent(UIComponent* component)
	{
		if (m_Components.IsEmpty())
			SelectComponent(component);

		m_Components.Push(component);
	}

	void UIContainer::Update(f32 dt)
	{
		if ((InputManager::GetControlState(-1, "Select").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Select").state == Controller::Pressed) && m_HoveredComponent)
			m_HoveredComponent->Activate();

		if ((InputManager::GetControlState(-1, "Left").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Left").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Left").axis < -50.0f) && m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Left));
		else if ((InputManager::GetControlState(-1, "Right").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Right").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Right").axis > 50.0f) && m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Right));
		else if ((InputManager::GetControlState(-1, "Down").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Down").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Down").axis > 50.0f) && m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Down));
		else if ((InputManager::GetControlState(-1, "Up").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Up").state == Controller::Pressed ||
			InputManager::GetControlState(0, "Up").axis < -50.0f) && m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Up));

		for (u32 i = 0; i < m_Components.Count(); ++i)
			m_Components[i]->Update(dt);
	}

	void UIContainer::Draw(sf::RenderStates states) const
	{
		for (u32 i = 0; i < m_Components.Count(); ++i)
			m_Components[i]->Draw(states);
	}

	void UIContainer::SelectComponent(UIComponent* component)
	{
		if (!component)
			return;

		if (m_HoveredComponent)
			m_HoveredComponent->SetState(UIComponent::Neutral);

		component->SetState(UIComponent::Hovered);
		m_HoveredComponent = component;
	}
}