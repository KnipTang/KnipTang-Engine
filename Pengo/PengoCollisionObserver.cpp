#include "PengoCollisionObserver.h"
#include "CollisionComponent.h"
#include <iostream>
#include "MovementComponent.h"
#include "PengoComponent.h"

void PengoCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string layer = actor->GetOwner()->GetLayer();
		std::cout << "Begin OverLapping: " << m_pOwner->GetLayer() << " With: ";
		
		if (layer == "Player")
		{
			std::cout << "Player\n";
		}
		else if (layer == "Enemy")
		{
			std::cout << "Enemy\n";

			m_pOwner->SetGameObjectPosition(actor->GetOwner()->GetGameObjectPosition().x, actor->GetOwner()->GetGameObjectPosition().y);
			actor->GetOwner()->RemoveGameObject();

			if (m_pOwner->HasComponent<PengoComponent>())
			{
				m_pOwner->GetComponent<PengoComponent>()->SetPengoIsKilled();
			}
		}
		else if (layer == "Wall")
		{
			std::cout << "Wall\n";

			if (m_pOwner->HasComponent<MovementComponent>())
			{
				m_pOwner->GetComponent<MovementComponent>()->SetHitWall(true);
			}
		}
	}
}
