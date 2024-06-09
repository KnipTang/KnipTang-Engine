#pragma once
#include <Component.h>

class EnemySpawnComponent : public dae::Component
{
public:
	EnemySpawnComponent(dae::GameObject* gameObject);
	~EnemySpawnComponent() override = default;

	EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
	EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;

	void SpawnEnemy();
};
