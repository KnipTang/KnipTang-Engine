#include "MovementComponent.h"

void MovementComponent::LateUpdate(float)
{
	if (m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();
		m_Direction *= -1; // invert direction
		objPos += m_Direction * m_Speed;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);

		m_HitWall = false;
	}
}
