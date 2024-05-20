#pragma once
#include "GameObject.h"
#include "CollisionObserver.h"

class InFrontObserver : public dae::CollisionObserver
{
public:
	InFrontObserver(dae::GameObject* gameObject) : m_pOwner(gameObject) {}
	//PengoCollisionObserver() {};
	~InFrontObserver() override = default;
	void NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor) override;
private:
	dae::GameObject* m_pOwner;
};


