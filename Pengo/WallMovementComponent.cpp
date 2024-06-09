#include "WallMovementComponent.h"
#include "CollisionComponent.h"
#include "WallCollisionObserver.h"
#include "WallComponent.h"
#include "GameConfig.h"
#include <cmath>
#include <SDL.h>

void WallMovementComponent::Update(float deltaTime)
{
	if (m_Vibrate)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();
		float vibrationOffsetX = std::sin(SDL_GetTicks64() * 10.f) * 0.1f;
		float vibrationOffsetY = std::sin(SDL_GetTicks64() * 10.f) * 0.1f;
		objPos.x += vibrationOffsetX;
		objPos.y += vibrationOffsetY;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);

		m_CurrentVibrationTime += deltaTime;
		if (m_CurrentVibrationTime >= m_MaxVibrationTime)
			m_Vibrate = false;
	}

	else if (m_Moving && !m_HitWall)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		m_TraveledElementLength += m_Speed * deltaTime;
		m_TraveledTotalLength += m_Speed * deltaTime;

		if (m_TraveledElementLength >= Config::ELEMENT_SIZE)
		{
			m_TraveledElementLength = 0;
			return;
		}

		objPos += m_Direction * m_Speed * deltaTime;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
	}
	else if (GetOwner()->GetGameObjectPosition().x != round(GetOwner()->GetGameObjectPosition().x) || GetOwner()->GetGameObjectPosition().y != round(GetOwner()->GetGameObjectPosition().y))
	{
		RoundOffWallPos();
	}
}

void WallMovementComponent::LateUpdate(float)
{
	m_HitWall = false;
}

void WallMovementComponent::Move(glm::vec3 direction, dae::GameObject* moverOwner)
{
	if (GetOwner()->HasComponent<WallComponent>())
		if (GetOwner()->GetComponent<WallComponent>()->IsWallDeleting())
			return;

	if (m_Moving)
	{
		return;
	}

	if (m_Vibrate)
	{
		RoundOffWallPos();
		m_HitWall = false;
		m_Vibrate = false;
	}

	if (m_HitWall)
	{
		return;
	}

	m_MoverOwner = moverOwner;

	GetOwner()->GetComponent<dae::CollisionComponent>()->AddObserver(new WallCollisionObserver(GetOwner()));

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

	if (m_TraveledTotalLength < Config::ELEMENT_SIZE && m_Moving)
	{
		if (GetOwner()->GetTag() != "HardWall")
		{
			if (GetOwner()->HasComponent<WallComponent>())
			{
				GetOwner()->GetComponent<WallComponent>()->DeleteWall();
			}
		}
	}
	m_TraveledTotalLength = 0;

	m_HitWall = hit;
}

void WallMovementComponent::RoundOffWallPos()
{
	glm::vec3 pos = GetOwner()->GetGameObjectPosition();
	pos.x -= Config::BORDER_SIZE;
	pos.y -= Config::BORDER_SIZE;
	pos = { round(pos.x / Config::ELEMENT_SIZE) * Config::ELEMENT_SIZE, round(pos.y / Config::ELEMENT_SIZE) * Config::ELEMENT_SIZE, pos.z };
	pos.x += Config::BORDER_SIZE;
	pos.y += Config::BORDER_SIZE;
	GetOwner()->SetGameObjectPosition(pos.x, pos.y);

	m_Moving = false;
}

void WallMovementComponent::Vibrate()
{
	if (GetOwner()->HasComponent<WallComponent>())
		if (GetOwner()->GetComponent<WallComponent>()->IsWallDeleting())
			return;

	m_Vibrate = true;
}
