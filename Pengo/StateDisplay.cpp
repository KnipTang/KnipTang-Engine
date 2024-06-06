#include "StateDisplay.h"
#include "TextObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

void StateDisplay::Notify(PengoEvents event, dae::Component* actor)
{
	if (event == PengoEvents::PlayerHit)
	{
		std::cout << "PlayerHit";
	}
	if (event == PengoEvents::PlayerDied)
	{
		// Update the display or take appropriate action
		std::string text = m_StateName + ": " + std::to_string(actor->GetOwner()->GetComponent<HealthComponent>()->GetCurrentLives());
		m_TextObject->SetText(text);
	}
	if (event == PengoEvents::PointsChanged)
	{
		// Update the display or take appropriate action
		std::string text = m_StateName + ": " + std::to_string(actor->GetOwner()->GetComponent<dae::ScoreComponent>()->GetPoints());
		m_TextObject->SetText(text);
	}
}

StateDisplay::StateDisplay(dae::GameObject* gameObject, std::string state, double startValue) 
	: Component(gameObject), m_StateName(state)
{
	m_TextObject = new dae::TextObject(GetOwner(), std::string(m_StateName + ": " + std::to_string(static_cast<int>(startValue))), dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
	GetOwner()->AddComponent(m_TextObject);
}