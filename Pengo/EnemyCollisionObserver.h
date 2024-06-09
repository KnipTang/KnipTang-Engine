#pragma once
#include <CollisionObserver.h>
#include <GameObject.h>

class EnemyCollisionObserver : public dae::CollisionObserver
{
public:
	EnemyCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	~EnemyCollisionObserver() override = default;

	EnemyCollisionObserver(const EnemyCollisionObserver& other) = delete;
	EnemyCollisionObserver(EnemyCollisionObserver&& other) = delete;
	EnemyCollisionObserver& operator=(const EnemyCollisionObserver& other) = delete;
	EnemyCollisionObserver& operator=(EnemyCollisionObserver&& other) = delete;

	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};
