#pragma once

namespace dae
{
	class CollisionComponent;
    enum class GameCollisionEvent {
        Collision,
		NoCollision
    };

    class CollisionObserver
    {
	public:
		CollisionObserver() = default;
		virtual ~CollisionObserver() = default;

		CollisionObserver(const CollisionObserver& other) = delete;
		CollisionObserver(CollisionObserver&& other) = delete;
		CollisionObserver& operator=(const CollisionObserver& other) = delete;
		CollisionObserver& operator=(CollisionObserver&& other) = delete;

		virtual void NotifyCollision(GameCollisionEvent event, CollisionComponent* actor) = 0;
    };
}

