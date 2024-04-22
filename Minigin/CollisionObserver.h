#pragma once
#include "Observer.h"

namespace dae
{
    class CollisionObserver : public Observer
    {
	public:
		void Notify(GameEvent event, Subject* actor) override;

		CollisionObserver() {};
		virtual ~CollisionObserver() { }
		CollisionObserver(const CollisionObserver& other) = delete;
		CollisionObserver(CollisionObserver&& other) = delete;
		CollisionObserver& operator=(const CollisionObserver& other) = delete;
		CollisionObserver& operator=(CollisionObserver&& other) = delete;
    };
}

