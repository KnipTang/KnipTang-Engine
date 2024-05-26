#include "EnemyMovementAIComponent.h"

void EnemyMovementAIComponent::FixedUpdate(float deltaTime)
{
	UpdateDirection();
	m_CurrentMoveTime += deltaTime;

	if (m_CurrentMoveTime >= m_MoveTime)
	{
		glm::vec3 objPos = GetOwner()->GetTransform()->GetWorldPosition();

		//m_TraveledElementLength += m_Speed * deltaTime;
		//if (m_TraveledElementLength >= 16.f)
		//{
		//	m_TraveledElementLength = 0;
		//	StopMoving();
		//
		//	return;
		//}

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