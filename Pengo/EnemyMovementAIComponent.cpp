#include "EnemyMovementAIComponent.h"

void EnemyMovementAIComponent::FixedUpdate(float deltaTime)
{
	if (!m_Moving)
	{
		UpdateDirection();
		RoundOffPosition();
		m_Moving = true;
	}
	else
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		m_TraveledElementLength += m_Speed * deltaTime;
		if (m_TraveledElementLength >= 16.f)
		{
			m_TraveledElementLength = 0;
			m_Moving = false;
		
			return;
		}

		objPos += m_Direction * m_Speed * deltaTime;
		GetOwner()->SetGameObjectPosition(objPos.x, objPos.y);
	}
}

void EnemyMovementAIComponent::UpdateDirection()
{
	dae::GameObject* closestPlayer = GetClosestPlayer();
	if (!closestPlayer)
		return;

	glm::vec3 closestPlayerPos = closestPlayer->GetGameObjectPosition();
	glm::vec3 enemyPos = GetOwner()->GetGameObjectPosition();

	float dx = closestPlayerPos.x - enemyPos.x;
	float dy = closestPlayerPos.y - enemyPos.y;
	
	m_Direction = {0,0,0};

	if (std::abs(dx) > std::abs(dy)) {
		m_Direction.x = (dx > 0) ? 1.0f : -1.0f;
	}
	else {
		m_Direction.y = (dy > 0) ? 1.0f : -1.0f;
	}
}


dae::GameObject* EnemyMovementAIComponent::GetClosestPlayer()
{
	m_Player = m_CurrentScene->GetGameObjectsWithTag("Player");

	if (m_Player.empty())
		return nullptr;

	glm::vec3 enemyPos = GetOwner()->GetGameObjectPosition();

	dae::GameObject* closestPlayer = m_Player.at(0);
	glm::vec3 closestPlayerPos = closestPlayer->GetGameObjectPosition();

	float closestDistanceSquared = CalculateDistanceSquared(closestPlayerPos, enemyPos);

	for (auto& player : m_Player)
	{
		glm::vec3 playerPos = player->GetGameObjectPosition();
		float distanceSquared = CalculateDistanceSquared(playerPos, enemyPos);

		if (distanceSquared < closestDistanceSquared) {
			closestPlayer = player;
			closestDistanceSquared = distanceSquared;
		}
	}

	return closestPlayer;
}

float EnemyMovementAIComponent::CalculateDistanceSquared(const glm::vec3& pos1, const glm::vec3& pos2) {
	glm::vec3 diff = pos1 - pos2;
	return glm::dot(diff, diff);
}

void EnemyMovementAIComponent::RoundOffPosition()
{
	glm::vec3 pos = GetOwner()->GetGameObjectPosition();
	pos.x -= 8;
	pos.y -= 8;
	pos = { round(pos.x / 16) * 16, round(pos.y / 16) * 16, pos.z };
	pos.x += 8;
	pos.y += 8;
	GetOwner()->SetGameObjectPosition(pos.x, pos.y);
}
