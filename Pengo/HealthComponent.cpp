#include "HealthComponent.h"
#include "GameObject.h"
#include "TextObject.h"
#include <iostream>

void dae::HealthComponent::DecreaseHealth(double health)
{
	m_CurrentHealth -= health;

	std::cout << m_CurrentHealth << '\n';

	if(m_CurrentHealth <= 0)
		DamageLives(1);
}

void dae::HealthComponent::DamageLives(int lives)
{
	m_CurrentLives -= lives;

	Die();
}

void dae::HealthComponent::Die()
{
	m_CurrentHealth = m_StartLives;

	NotifyObservers(GameEvent::PlayerDied);

	if (m_CurrentLives == 0)
		GetOwner()->RemoveGameObject();
}