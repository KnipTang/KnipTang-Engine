#include "StateDisplay.h"
#include "GameObject.h"
#include "Component.h"
#include "TextObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"

StateDisplay::StateDisplay(dae::GameObject* gameObject, std::string state, double startValue) 
	: Component(gameObject), m_StateName(state)
{
	m_TextObject = new dae::TextObject(GetOwner(), std::string(m_StateName + ": " + std::to_string(static_cast<int>(startValue))), dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
	GetOwner()->AddComponent(m_TextObject);
}

void StateDisplay::Notify(PengoEvents event, dae::Component* actor)
{
	if (event == PengoEvents::PlayerHit)
	{

	}
	if (event == PengoEvents::PlayerDied)
	{
		std::string text = m_StateName + ": " + std::to_string(actor->GetOwner()->GetComponent<HealthComponent>()->GetCurrentLives());
		m_TextObject->SetText(text);
	}
	if (event == PengoEvents::PointsChanged)
	{
		std::string text = m_StateName + ": " + std::to_string(actor->GetOwner()->GetComponent<ScoreComponent>()->GetScore());
		m_TextObject->SetText(text);
	}
}
