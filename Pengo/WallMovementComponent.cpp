#include "WallMovementComponent.h"

void WallMovementComponent::Update(float deltaTime)
{
	if (m_Moving && !m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		m_TraveledLength += m_Speed * deltaTime;
		if (m_TraveledLength >= 16.f)
		{
			m_TraveledLength = 0;
			return;
		}

		objPos += m_Direction * m_Speed * deltaTime;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
	}
	else if (GetOwner()->GetGameObjectPosition().x != round(GetOwner()->GetGameObjectPosition().x) || GetOwner()->GetGameObjectPosition().y != round(GetOwner()->GetGameObjectPosition().y))
	{
		glm::vec3 pos = GetOwner()->GetGameObjectPosition();
		pos.x -= 8;
		pos.y -= 8;
		pos = { round(pos.x / 16) * 16, round(pos.y / 16) * 16, pos.z };
		pos.x += 8;
		pos.y += 8;
		GetOwner()->SetGameObjectPosition(pos.x, pos.y);

		m_Moving = false;
	}
}

void WallMovementComponent::LateUpdate(float)
{
	m_HitWall = false;
}

void WallMovementComponent::Move(glm::vec3 direction)
{
	if (m_Moving)
	{
		return;
	}

	if (m_HitWall)
	{
		return;
	}

	m_Moving = true;
	m_Direction = direction;

	m_StartPos = GetOwner()->GetTransform()->GetWorldPosition();
}
