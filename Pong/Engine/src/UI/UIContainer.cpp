#include "UIContainer.h"

#include <IO/InputManager.h>

namespace Soul
{
	UIContainer::UIContainer() :
		m_Components(),
		m_HoveredComponent(nullptr)
	{
	}

	UIContainer::UIContainer(UIContainer&& other) noexcept :
		m_Components(std::move(other.m_Components)),
		m_HoveredComponent(other.m_HoveredComponent)
	{
	}

	UIContainer::~UIContainer()
	{
		for (u32 i = 0; i < m_Components.Count(); ++i)
			MemoryManager::FreeMemory(m_Components[i]);
	}

	UIContainer& UIContainer::operator=(UIContainer&& other) noexcept
	{
		m_Components = std::move(other.m_Components);
		m_HoveredComponent = other.m_HoveredComponent;

		return *this;
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

		Controller::ControlState horiMappingController = InputManager::GetControlState(0, "Left");
		Controller::ControlState vertMappingController = InputManager::GetControlState(0, "Down");
		Controller::ControlState leftMappingKeyboard = InputManager::GetControlState(-1, "Left");
		Controller::ControlState rightMappingKeyboard = InputManager::GetControlState(-1, "Right");
		Controller::ControlState downMappingKeyboard = InputManager::GetControlState(-1, "Down");
		Controller::ControlState upMappingKeyboard = InputManager::GetControlState(-1, "Up");

		if (rightMappingKeyboard.state == Controller::Pressed ||
			(horiMappingController.axisHeld == Controller::Pressed && horiMappingController.axis > 0)
			&& m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Right));
		else if (leftMappingKeyboard.state == Controller::Pressed ||
			(horiMappingController.axisHeld == Controller::Pressed && horiMappingController.axis < 0)
			&& m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Left));
		else if (downMappingKeyboard.state == Controller::Pressed ||
			(vertMappingController.axisHeld == Controller::Pressed)
			&& m_HoveredComponent)
			SelectComponent(m_HoveredComponent->GetConnection(UIComponent::Down));
		else if (upMappingKeyboard.state == Controller::Pressed ||
			(vertMappingController.axisHeld == Controller::Pressed)
			&& m_HoveredComponent)
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