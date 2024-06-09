#include "HealthComponent.h"
#include "GameObject.h"
#include "StateDisplay.h"

int HealthComponent::DamageLives(int lives)
{
	m_CurrentLives -= lives;
	NotifyObservers(PengoEvents::PlayerHit);
	return m_CurrentLives;
}

void HealthComponent::Die()
{
	NotifyObservers(PengoEvents::PlayerDied);

	if (m_CurrentLives == 0)
		GetOwner()->RemoveGameObject();
}