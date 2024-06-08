#include "MovementComponent.h"
#include "PengoComponent.h"
#include "InFrontViewComponent.h"
#include <memory>
void MovementComponent::Update(float deltaTime)
{
	if (m_Stunned) 
	{
		auto now = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_StunStartTime).count();
		if (duration >= m_StunDuration) {
			m_Stunned = false;
		}
	}
	else if (m_Moving && !m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();
	
		m_TraveledElementLength += m_Speed * deltaTime;
		if (m_TraveledElementLength >= 16.f)
		{
			m_TraveledElementLength = 0;
			StopMoving();

			return;
		}
	
		objPos += m_Direction * m_Speed * deltaTime;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
	}
	else if(GetOwner()->GetGameObjectPosition().x != round(GetOwner()->GetGameObjectPosition().x) || GetOwner()->GetGameObjectPosition().y != round(GetOwner()->GetGameObjectPosition().y))
	{
		glm::vec3 pos = GetOwner()->GetGameObjectPosition();
		pos.x -= 8;
		pos.y -= 8;
		pos = { round(pos.x / 16) * 16, round(pos.y / 16) * 16, pos.z };
		pos.x += 8;
		pos.y += 8;
		GetOwner()->SetGameObjectPosition(pos.x, pos.y);
		
		StopMoving();
	}
}

void MovementComponent::LateUpdate(float)
{
	m_HitWall = false;
}

void MovementComponent::Move(float , glm::vec3 direction)
{
	if (m_Moving || m_Stunned)
	{
		return;
	}

	for (unsigned int i = 0; i < GetOwner()->GetChildCount(); i++)
	{
		if (GetOwner()->GetChildAt(i)->HasComponent<InFrontViewComponent>())
			GetOwner()->GetChildAt(i)->GetComponent<InFrontViewComponent>()->UpdatePosition(direction);
	}

	if (m_HitWall)
	{
		StopMoving();
		return;
	}

	m_Moving = true;
	m_Direction = direction;

	m_StartPos = GetOwner()->GetTransform()->GetWorldPosition();

}

void MovementComponent::StunForSeconds(float seconds)
{
	m_Stunned = true;
	m_StunStartTime = std::chrono::steady_clock::now();
	m_StunDuration = seconds;
}

void MovementComponent::StopMoving()
{
	m_Moving = false;
	if (GetOwner()->HasComponent<PengoComponent>())
	{
		if(!GetOwner()->GetComponent<PengoComponent>()->IsPengoKilled())
			GetOwner()->GetComponent<PengoComponent>()->SetState(std::make_unique<Idle>(GetOwner()));
	}
}
