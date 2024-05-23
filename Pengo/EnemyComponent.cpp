#include "EnemyComponent.h"
#include "GameConfig.h"
void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	if (direction.x < 0 || direction.y < 0)
		GetOwner()->SetGameObjectPosition(direction.x, direction.y);
	else
		GetOwner()->SetGameObjectPosition(direction.x * Config_ElementSize, direction.y * Config_ElementSize);
}
