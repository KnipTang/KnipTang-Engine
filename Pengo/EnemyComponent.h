#pragma once
#include <Component.h>
#include "GameObject.h"
class EnemyComponent : public dae::Component
{
public:
	void Update(float) override {};
	void LateUpdate(float) override {};
	void FixedUpdate(float) override {}
	void Render() const override {}

	void SetHitByWallPos(glm::vec3 direction);
	bool WasHitByWall() { return m_WasHitByWall; }

	void Dies();

	EnemyComponent(dae::GameObject* gameObject) : dae::Component(gameObject) {};
	virtual ~EnemyComponent() { }
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;
private:
	bool m_WasHitByWall;
};

