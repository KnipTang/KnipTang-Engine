#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class InFrontObserver : public dae::CollisionObserver
{
public:
	InFrontObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	~InFrontObserver() override = default;

	InFrontObserver(const InFrontObserver& other) = delete;
	InFrontObserver(InFrontObserver&& other) = delete;
	InFrontObserver& operator=(const InFrontObserver& other) = delete;
	InFrontObserver& operator=(InFrontObserver&& other) = delete;

	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};
