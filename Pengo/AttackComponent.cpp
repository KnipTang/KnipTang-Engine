#include "AttackComponent.h"
#include "WallMovementComponent.h"
#include "PengoComponent.h"

void AttackComponent::Attack()
{
	if (m_AttackReady && m_JoyStickPressed)
	{
		glm::vec3 direction{ 0,0,0 };

		if (GetOwner()->HasComponent<PengoComponent>())
			direction = GetOwner()->GetComponent<PengoComponent>()->GetCurrentDirection();

		if(m_ObjectInfront->HasComponent<WallMovementComponent>())
		{
			m_ObjectInfront->GetComponent<WallMovementComponent>()->Move(direction, GetOwner());
		}
	}
}

void AttackComponent::JoyStickPressed()
{
	m_JoyStickPressed = true;
}
