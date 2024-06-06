#include "HealthComponent.h"
#include "GameObject.h"
#include "TextObject.h"
#include "StateDisplay.h"
#include <iostream>

int HealthComponent::DamageLives(int lives)
{
	m_CurrentLives -= lives;
	NotifyObservers(PengoEvents::PlayerHit);
	return m_CurrentLives;

	//Die();
}

void HealthComponent::Die()
{
	NotifyObservers(PengoEvents::PlayerDied);

	if (m_CurrentLives == 0)
		GetOwner()->RemoveGameObject();
}