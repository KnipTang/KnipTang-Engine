#include "WallCollisionObserver.h"
#include "CollisionComponent.h"
#include "WallMovementComponent.h"
#include "EnemyComponent.h"
#include "RenderComponent.h"
#include "EnemyMovementAIComponent.h"
#include <iostream>

void WallCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string layer = actor->GetOwner()->GetLayer();

		if (layer == "Player")
		{
		}
		if (layer == "Enemy")
		{
			if (m_pOwner->HasComponent<WallMovementComponent>())
			{
				if (m_pOwner->GetComponent<WallMovementComponent>()->IsVibrating())
				{
					if (actor->GetOwner()->HasComponent<EnemyMovementAIComponent>())
						actor->GetOwner()->GetComponent<EnemyMovementAIComponent>()->StunEnemy();
				}
				else if (m_pOwner->GetComponent<WallMovementComponent>()->IsWallMoving())
				{
					glm::vec3 currentDirection = m_pOwner->GetComponent<WallMovementComponent>()->GetDirection();

					if (actor->GetOwner()->HasComponent<EnemyComponent>())
						actor->GetOwner()->GetComponent<EnemyComponent>()->SetHitByWallPos(currentDirection);

					if (actor->GetOwner()->HasComponent<EnemyMovementAIComponent>())
						actor->GetOwner()->RemoveComponent(actor->GetOwner()->GetComponent<EnemyMovementAIComponent>());
					//m_pOwner->RemoveComponent(m_pOwner->GetComponent<dae::RenderComponent>());

					actor->GetOwner()->SetParent(m_pOwner, false);
					//actor->GetOwner()->RemoveGameObject();
				}
			}
		}
		if (layer == "Wall")
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
