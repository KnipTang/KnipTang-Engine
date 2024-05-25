#pragma once
#include <CollisionObserver.h>
#include <GameObject.h>
class EnemyCollisionObserver : public dae::CollisionObserver
{
public:
	EnemyCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	//PengoCollisionObserver() {};
	~EnemyCollisionObserver() override = default;
	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};

