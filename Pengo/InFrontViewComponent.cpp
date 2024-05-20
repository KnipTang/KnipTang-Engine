#include "InFrontViewComponent.h"
#include "GameObject.h"
#include "GameConfig.h"

void InFrontViewComponent::UpdatePosition(glm::vec3 direction)
{
	GetOwner()->SetGameObjectPosition(direction.x * Config_ElementSize, direction.y * Config_ElementSize);
}
