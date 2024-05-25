#include "EnemyComponent.h"
#include "GameConfig.h"
#include "EnemyCollisionObserver.h"
#include "CollisionComponent.h"

void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	if (direction.x < 0 || direction.y < 0)
		GetOwner()->SetGameObjectPosition(direction.x, direction.y);
	else
		GetOwner()->SetGameObjectPosition(direction.x * Config_ElementSize, direction.y * Config_ElementSize);
	
	GetOwner()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(GetOwner()));

	m_WasHitByWall = true;
}

void EnemyComponent::Dies()
{
	GetOwner()->RemoveGameObject();
}
