#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class WallCollisionObserver : public dae::CollisionObserver
{
public:
	WallCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	~WallCollisionObserver() override = default;

	WallCollisionObserver(const WallCollisionObserver& other) = delete;
	WallCollisionObserver(WallCollisionObserver&& other) = delete;
	WallCollisionObserver& operator=(const WallCollisionObserver& other) = delete;
	WallCollisionObserver& operator=(WallCollisionObserver&& other) = delete;

	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};
