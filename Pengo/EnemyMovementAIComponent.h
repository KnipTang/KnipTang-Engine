#pragma once
#include <Component.h>
class EnemyMovementAIComponent : public dae::Component
{
public:
	EnemyMovementAIComponent(dae::GameObject* gameObject) : dae::Component(gameObject) { };
	virtual ~EnemyMovementAIComponent() { }
	EnemyMovementAIComponent(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent(EnemyMovementAIComponent&& other) = delete;
	EnemyMovementAIComponent& operator=(const EnemyMovementAIComponent& other) = delete;
	EnemyMovementAIComponent& operator=(EnemyMovementAIComponent&& other) = delete;

private:

};

