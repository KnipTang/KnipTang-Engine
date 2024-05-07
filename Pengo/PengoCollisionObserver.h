#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class PengoCollisionObserver : public dae::CollisionObserver
{
public:
	PengoCollisionObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	//PengoCollisionObserver() {};
	~PengoCollisionObserver() override = default;
	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};

