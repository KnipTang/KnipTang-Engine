#include "PengoCollisionObserver.h"
#include "CollisionComponent.h"
#include <iostream>
#include "MovementComponent.h"
#include "PengoComponent.h"

void PengoCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
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

			actor->GetOwner()->RemoveGameObject();

			if (m_pOwner->HasComponent<PengoComponent>())
			{
				m_pOwner->GetComponent<PengoComponent>()->SetState(std::make_unique<DyingState>(actor->GetOwner()));
			}
		}
		else if (tag == "Wall")
		{
			std::cout << "Wall\n";

			if (m_pOwner->HasComponent<MovementComponent>())
			{
				m_pOwner->GetComponent<MovementComponent>()->SetHitWall(true);
			}
		}
	}
}
