#include "WallCollisionObserver.h"
#include "CollisionComponent.h"
#include "WallMovementComponent.h"
#include <iostream>

void WallCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string tag = actor->GetOwner()->GetTag();
		std::cout << "Begin OverLapping: " << m_pOwner->GetTag() << " With: ";

		if (tag == "Player")
		{
			std::cout << "Player\n";
		}
		else if (tag == "Enemy")
		{
			std::cout << "Enemy\n";

			//m_pOwner->SetGameObjectPosition(actor->GetOwner()->GetGameObjectPosition().x, actor->GetOwner()->GetGameObjectPosition().y);
			//actor->GetOwner()->RemoveGameObject();

			//if (m_pOwner->HasComponent<PengoComponent>())
			//{
			//	m_pOwner->GetComponent<PengoComponent>()->SetState(std::make_unique<DyingState>(m_pOwner));
			//}
		}
		else if (tag == "Wall")
		{
			std::cout << "Wall\n";

			if (m_pOwner->HasComponent<WallMovementComponent>())
			{
				m_pOwner->GetComponent<WallMovementComponent>()->SetHitWall(true);
			}
		}
	}
}
