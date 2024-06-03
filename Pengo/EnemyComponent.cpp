#include "EnemyComponent.h"
#include "GameConfig.h"
#include "EnemyCollisionObserver.h"
#include "CollisionComponent.h"
#include "Animation.h"

EnemyComponent::EnemyComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{

}

void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);

	m_WasHitByWall = true;
}

void EnemyComponent::Dies()
{
	GetOwner()->RemoveGameObject();
}

