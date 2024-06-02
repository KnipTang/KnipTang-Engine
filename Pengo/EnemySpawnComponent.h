#pragma once
#include <Component.h>
class EnemySpawnComponent : public dae::Component
{
public:
	EnemySpawnComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
	{
	}

	virtual ~EnemySpawnComponent() { }

	void Update(float /*deltaTime*/) override { SpawnEnemy(); }

	void SpawnEnemy();

	EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
	EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;
};

