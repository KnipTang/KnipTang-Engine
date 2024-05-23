#include "WallMovementComponent.h"
#include "CollisionComponent.h"
#include "WallCollisionObserver.h"
#include <iostream>
void WallMovementComponent::Update(float deltaTime)
{
	if (m_Moving && !m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		m_TraveledElementLength += m_Speed * deltaTime;
		m_TraveledTotalLength += m_Speed * deltaTime;

		if (m_TraveledElementLength >= 16.f)
		{
			m_TraveledElementLength = 0;
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

	//if (GetOwner()->HasComponent<WallCollisionObserver>() == false)
	//{
	//	GetOwner()->AddComponent(new WallCollisionObserver(GetOwner()));
	//}
	GetOwner()->GetComponent<dae::CollisionComponent>()->AddObserver(new WallCollisionObserver(GetOwner()));
	//GetOwner()->AddComponent<new WallCollisionObserver>(GetOwner());

	m_Moving = true;
	m_Direction = direction;

	m_StartPos = GetOwner()->GetTransform()->GetWorldPosition();
}

void WallMovementComponent::SetHitWall(bool hit)
{
	unsigned int observerCount = static_cast<unsigned int>(GetOwner()->GetComponent<dae::CollisionComponent>()->GetObserversCount());
	for (unsigned int i = 0; i < observerCount; i++)
	{
		GetOwner()->GetComponent<dae::CollisionComponent>()->RemoveObserver(GetOwner()->GetComponent<dae::CollisionComponent>()->GetObserverAt(i));
	}
	

	if (m_TraveledTotalLength < 16 && m_Moving)
	{
		//GetOwner()->SetGameObjectPosition(5, 5);
		GetOwner()->RemoveGameObject();
	}
	m_TraveledTotalLength = 0;

	for (int i = 0; i < GetOwner()->GetChildCount(); i++)
	{
		GetOwner()->GetChildAt(i)->RemoveGameObject();
	}
	GetOwner()->RemoveAllChildren();

	m_HitWall = hit;
	m_Moving = !hit;
}
