#pragma once
#include <Component.h>
#include <memory>
#include "GameObject.h"
#include "EnemyState.h"

class EnemyComponent : public dae::Component
{
public:
	void Update(float) override;
	void LateUpdate(float) override {};
	void FixedUpdate(float) override {}
	void Render() const override {}

	void SetHitByWallPos(glm::vec3 direction);
	bool WasHitByWall() { return m_WasHitByWall; }

	void Dies();

	void SetState(std::unique_ptr<EnemyState> state)
	{
		m_State = std::move(state);
	}

	EnemyComponent(dae::GameObject* gameObject);
	virtual ~EnemyComponent() { }
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;
private:
	dae::GameObject* GetEnemySpawnBlock();

	std::unique_ptr<EnemyState> m_State;

	bool m_WasHitByWall;
};

