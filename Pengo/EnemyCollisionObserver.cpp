#include "EnemyCollisionObserver.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "Component.h"
#include "WallMovementComponent.h"
#include "WallComponent.h"

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
		if (tag == "Wall")
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
				if(actor->GetOwner()->HasComponent<WallComponent>())
				{
					actor->GetOwner()->GetComponent<WallComponent>()->DeleteWall();
				}
			}
		}
	}
}
