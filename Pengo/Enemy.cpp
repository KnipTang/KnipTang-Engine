#include "Enemy.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"

Enemy::Enemy(int posX, int posY)
{
	m_Actor.get()->AddComponent(new dae::RenderComponent(m_Actor.get()));
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 9, 16, 16);
	m_Actor.get()->SetGameObjectPosition(static_cast<float>(posX), static_cast<float>(posY));
	m_Actor.get()->AddComponent(new dae::CollisionComponent(m_Actor.get(), 16, 16));
	m_Actor.get()->AddComponent(new dae::HealthComponent(m_Actor.get()));
	m_Actor.get()->SetTag("Enemy");
}
