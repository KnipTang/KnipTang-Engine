#pragma once
#include <Component.h>
#include "GameObject.h"
#include "Scene.h"
class EnemyMovementAIComponent : public dae::Component
{
public:
	void FixedUpdate(float deltaTime) override;

	EnemyMovementAIComponent(dae::GameObject* gameObject, float speed = 16.f) : dae::Component(gameObject), m_Speed(speed)
	{
		m_CurrentScene = dae::SceneManager::GetInstance().GetSceneByName("Demo");
		m_Player = m_CurrentScene->GetGameObjectsWithLayer("Player");
	};

	void StopMoving() { m_Moving = false; };

	void StunEnemy();

	virtual ~EnemyMovementAIComponent() { }
	EnemyMovementAIComponent(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent(EnemyMovementAIComponent&& other) = delete;
	EnemyMovementAIComponent& operator=(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent& operator=(EnemyMovementAIComponent&& other) = delete;

private:
	dae::GameObject* GetClosestPlayer();
	void UpdateDirection();
	float CalculateDistanceSquared(const glm::vec3& pos1, const glm::vec3& pos2);

	void RoundOffPosition();

	bool m_Moving;

	float m_Speed;

	float m_TraveledElementLength;

	dae::Scene* m_CurrentScene;

	std::vector<dae::GameObject*> m_Player;

	glm::vec3 m_Direction{ 1,0,0 };
	glm::vec3 m_LastDirection{ 0,0,0 };

	bool m_Stunned;
	float m_CurrentStunnedTime = 0;
	float m_MaxStunnedTime = 5;
};
