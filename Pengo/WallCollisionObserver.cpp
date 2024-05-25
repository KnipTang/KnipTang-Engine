#include "WallCollisionObserver.h"
#include "CollisionComponent.h"
#include "WallMovementComponent.h"
#include "EnemyComponent.h"
#include <iostream>

void WallCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string tag = actor->GetOwner()->GetTag();

		if (tag == "Player")
		{
		}
		if (tag == "Enemy")
		{
			if (m_pOwner->HasComponent<WallMovementComponent>())
			{
				if (m_pOwner->GetComponent<WallMovementComponent>()->IsWallMoving())
				{
					glm::vec3 currentDirection = m_pOwner->GetComponent<WallMovementComponent>()->GetDirection();

					if (actor->GetOwner()->HasComponent<EnemyComponent>())
						actor->GetOwner()->GetComponent<EnemyComponent>()->SetHitByWallPos(currentDirection);



					actor->GetOwner()->SetParent(m_pOwner, false);
					//actor->GetOwner()->RemoveGameObject();
				}
			}
		}
		if (tag == "Wall")
		{
			std::cout << "Wall\n";
			if (m_pOwner->HasComponent<WallMovementComponent>())
			{
				if(m_pOwner->GetComponent<WallMovementComponent>()->IsWallMoving())
					m_pOwner->GetComponent<WallMovementComponent>()->SetHitWall(true);
			}
		}
	}
}
