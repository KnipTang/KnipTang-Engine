#include "MovementComponent.h"
#include "PengoComponent.h"
#include <memory>
void MovementComponent::Update(float deltaTime)
{
	if (m_Moving && !m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		m_TraveledLength += m_Speed * deltaTime;
		if (m_TraveledLength >= 16.f)
		{
			m_Moving = false;
			m_TraveledLength = 0;

			objPos = m_StartPos + m_Direction * 16.f;
			GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);

			if (GetOwner()->HasComponent<PengoComponent>())
			{
				GetOwner()->GetComponent<PengoComponent>()->SetState(std::make_unique<Idle>(GetOwner()));
			}
			return;
		}

		objPos += m_Direction * m_Speed * deltaTime;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
	}
}

void MovementComponent::LateUpdate(float)
{
	if (m_HitWall)
	{
		GetOwner()->SetGameObjectPosition(m_StartPos.x, m_StartPos.y);

		if (GetOwner()->HasComponent<PengoComponent>())
		{
			GetOwner()->GetComponent<PengoComponent>()->SetState(std::make_unique<Idle>(GetOwner()));
		}

		m_Moving = false;
		m_HitWall = false;
	}
}

void MovementComponent::Move(float , glm::vec3 direction)
{
	if (m_Moving) return;

	m_Moving = true;
	m_Direction = direction;

	m_StartPos = GetOwner()->GetTransform()->GetWorldPosition();
}
