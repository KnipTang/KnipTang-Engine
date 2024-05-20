#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class WallCollisionObserver : public dae::CollisionObserver
{
public:
	WallCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	//PengoCollisionObserver() {};
	~WallCollisionObserver() override = default;
	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};


