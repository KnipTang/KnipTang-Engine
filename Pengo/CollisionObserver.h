#pragma once
#include "GameObject.h"
#include "Observer.h"

namespace dae
{
	//enum class GameTags
	//{
	//	Player,
	//	Enemy
	//};

    class CollisionObserver : public Observer
    {
	public:
		void Notify(GameEvent event, Subject* actor) override;


		CollisionObserver(GameObject* gameObject) : m_pOwner(gameObject) {}
		virtual ~CollisionObserver() { }
		CollisionObserver(const CollisionObserver& other) = delete;
		CollisionObserver(CollisionObserver&& other) = delete;
		CollisionObserver& operator=(const CollisionObserver& other) = delete;
		CollisionObserver& operator=(CollisionObserver&& other) = delete;

    private:
		GameObject* m_pOwner;
    };
}

