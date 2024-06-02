#include "EnemyComponent.h"
#include "GameConfig.h"
#include "EnemyCollisionObserver.h"
#include "CollisionComponent.h"

void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);
	//if (direction.x < 0 || direction.y < 0)
	//	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);
	//else
	//	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);
	
	//GetOwner()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(GetOwner()));

	m_WasHitByWall = true;
}

void EnemyComponent::Dies()
{
	GetOwner()->RemoveGameObject();
}
