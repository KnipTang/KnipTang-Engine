#pragma once

namespace dae
{
	class CollisionComponent;
    enum class GameCollisionEvent {
        Collision
    };

    class CollisionObserver
    {
	public:

		//CollisionObserver(GameObject* gameObject) : m_pOwner(gameObject) {}
		CollisionObserver() {}
		virtual ~CollisionObserver() { }
		CollisionObserver(const CollisionObserver& other) = delete;
		CollisionObserver(CollisionObserver&& other) = delete;
		CollisionObserver& operator=(const CollisionObserver& other) = delete;
		CollisionObserver& operator=(CollisionObserver&& other) = delete;

		virtual void NotifyCollision(GameCollisionEvent event, CollisionComponent* actor) = 0;
    protected:
    };
}

