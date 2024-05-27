#include "InFrontViewComponent.h"
#include "GameObject.h"
#include "GameConfig.h"

void InFrontViewComponent::UpdatePosition(glm::vec3 direction)
{
	if(direction.x < 0 || direction.y < 0)
		GetOwner()->SetGameObjectPosition(direction.x, direction.y);
	else
		GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);

}
