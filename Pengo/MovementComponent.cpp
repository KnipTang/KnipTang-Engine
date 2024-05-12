#include "MovementComponent.h"

void MovementComponent::LateUpdate(float)
{
	if (m_HitWall)
	{
		m_Direction *= -1;
		Move(m_Direction);

		m_HitWall = false;
	}
}

void MovementComponent::Move(glm::vec3 direction)
{
	m_Direction = direction;

	glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();
	objPos += m_Direction * m_Speed;
	GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
}
