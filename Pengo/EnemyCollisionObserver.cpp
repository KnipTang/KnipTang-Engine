#include "EnemyCollisionObserver.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "Component.h"
#include "WallMovementComponent.h"
#include "WallComponent.h"
#include "EnemyMovementAIComponent.h"

void EnemyCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string tag = actor->GetOwner()->GetTag();

		if (tag == "Player")
		{
		}
		if (tag == "Enemy")
		{
			
		}
		if (tag == "Wall" || tag == "HardWall")
		{
			bool wasHitByWall = false;

			{
				if (m_pOwner->HasComponent<EnemyComponent>())
					wasHitByWall = m_pOwner->GetComponent<EnemyComponent>()->WasHitByWall();
			}

			if (wasHitByWall)
			{
				if (m_pOwner->GetParent() == nullptr)
					return;
				if (m_pOwner->GetParent() != actor->GetOwner())
				{
					m_pOwner->GetComponent<EnemyComponent>()->Dies();
				}
			}
			else
			{
				if (tag == "HardWall")
				{
					if (m_pOwner->HasComponent<EnemyMovementAIComponent>())
						m_pOwner->GetComponent<EnemyMovementAIComponent>()->StopMoving();
					return;
				}

				if (actor->GetOwner()->HasComponent<WallMovementComponent>())
					if (actor->GetOwner()->GetComponent<WallMovementComponent>()->IsWallMoving())
						return;

				if(actor->GetOwner()->HasComponent<WallComponent>())
				{
					actor->GetOwner()->GetComponent<WallComponent>()->DeleteWall();
					actor->GetOwner()->SetParent(m_pOwner, true);
				}
			}
		}
	}
}
