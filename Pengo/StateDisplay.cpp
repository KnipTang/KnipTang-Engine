#include "StateDisplay.h"
#include "TextObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
void dae::StateDisplay::Notify(GameEvent event, Subject* actor)
{
	if (event == GameEvent::PlayerDied)
	{
		// Update the display or take appropriate action
		std::string text = m_StateName + ": " + std::to_string(actor->GetGameObject()->GetComponent<dae::HealthComponent>()->GetLives());
		m_TextObject->SetText(text);
	}
	if (event == GameEvent::PointsChanged)
	{
		// Update the display or take appropriate action
		std::string text = m_StateName + ": " + std::to_string(actor->GetGameObject()->GetComponent<ScoreComponent>()->GetPoints());
		m_TextObject->SetText(text);
	}
}

dae::StateDisplay::StateDisplay(GameObject* gameObject, std::string state, double startValue) 
	: Component(gameObject), m_StateName(state)
{
	m_TextObject = new TextObject(GetOwner(), std::string(m_StateName + ": " + std::to_string(static_cast<int>(startValue))), ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
	GetOwner()->AddComponent(m_TextObject);
}
