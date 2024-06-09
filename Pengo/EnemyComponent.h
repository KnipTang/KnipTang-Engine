#pragma once
#include <Component.h>
#include <memory>
#include "GameObject.h"
#include "EnemyState.h"

class EnemyComponent : public dae::Component
{
public:
	EnemyComponent(dae::GameObject* gameObject);
	~EnemyComponent() override = default;

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	void Update(float) override;

	void SetHitByWallPos(glm::vec3 direction);
	bool WasHitByWall() { return m_WasHitByWall; }

	void Dies();

	void SetState(std::unique_ptr<EnemyState> state) { m_State = std::move(state); }

private:
	dae::GameObject* GetEnemySpawnBlock();

	std::unique_ptr<EnemyState> m_State;

	bool m_WasHitByWall;
};

