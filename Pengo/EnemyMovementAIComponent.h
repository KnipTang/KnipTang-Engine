#pragma once
#include <Component.h>
#include "GameObject.h"
#include "Scene.h"
class EnemyMovementAIComponent : public dae::Component
{
public:
	void FixedUpdate(float deltaTime) override;

	EnemyMovementAIComponent(dae::GameObject* gameObject) : dae::Component(gameObject) 
	{
		m_CurrentScene = dae::SceneManager::GetInstance().GetSceneByName("Demo");
		m_Player = m_CurrentScene->GetGameObjectsWithTag("Player");
	};
	virtual ~EnemyMovementAIComponent() { }
	EnemyMovementAIComponent(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent(EnemyMovementAIComponent&& other) = delete;
	EnemyMovementAIComponent& operator=(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent& operator=(EnemyMovementAIComponent&& other) = delete;

private:
	dae::GameObject* GetClosestPlayer();
	void UpdateDirection();
	float CalculateDistanceSquared(const glm::vec3& pos1, const glm::vec3& pos2);

	bool m_Move;
	float m_CurrentMoveTime;
	float m_MoveTime;

	float m_Speed = 6.f;

	dae::Scene* m_CurrentScene;

	std::vector<dae::GameObject*> m_Player;

	glm::vec3 m_Direction{ 1,0,0 };
};
