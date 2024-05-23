#include "AttackComponent.h"
#include "WallMovementComponent.h"
#include "PengoComponent.h"
#include <iostream>

void AttackComponent::Attack()
{
	//m_ObjectInfront->SetGameObjectPosition(5, 5);
	if (m_AttackReady)
	{
		glm::vec3 direction{ 0,0,0 };

		if (GetOwner()->HasComponent<PengoComponent>())
			direction = GetOwner()->GetComponent<PengoComponent>()->GetCurrentDirection();

		if(m_ObjectInfront->HasComponent<WallMovementComponent>())
		{
			m_ObjectInfront->GetComponent<WallMovementComponent>()->Move(direction);
		}
	}
}
