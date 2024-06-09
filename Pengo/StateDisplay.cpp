#include "StateDisplay.h"
#include "GameObject.h"
#include "Component.h"
#include "TextObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "ScoreComponent.h"

StateDisplay::StateDisplay(dae::GameObject* gameObject, std::string state, double startValue) 
	: Component(gameObject), m_StateName(state)
{
	auto livesDisplay = std::make_unique<dae::GameObject>();
	m_TextObject = new dae::TextObject(GetOwner(), std::string(m_StateName + ": " + std::to_string(static_cast<int>(startValue))), dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15));
	livesDisplay->AddComponent(m_TextObject);

	if(GetOwner()->GetTag() == "Player1")
		livesDisplay->SetGameObjectPosition(16, 16);
	else
		livesDisplay->SetGameObjectPosition(200, 16);

	livesDisplay->SetParent(GetOwner(), true);

	dae::SceneManager::GetInstance().GetSceneByName("GameLayout")->Add(std::move(livesDisplay));
}

void StateDisplay::Notify(PengoEvents event, dae::Component* actor)
{
	if (event == PengoEvents::PlayerHit)
	{
		std::string text = m_StateName + ": " + std::to_string(actor->GetOwner()->GetComponent<HealthComponent>()->GetCurrentLives());
		m_TextObject->SetText(text);
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
