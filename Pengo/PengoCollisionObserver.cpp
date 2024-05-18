#include "PengoCollisionObserver.h"
#include "CollisionComponent.h"
#include <iostream>
#include "MovementComponent.h"
#include "PengoComponent.h"
#include "DenyCollisionComponent.h"

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

			m_pOwner->SetGameObjectPosition(actor->GetOwner()->GetGameObjectPosition().x, actor->GetOwner()->GetGameObjectPosition().y);
			actor->GetOwner()->RemoveGameObject();

			if (m_pOwner->HasComponent<PengoComponent>())
			{
				m_pOwner->GetComponent<PengoComponent>()->SetState(std::make_unique<DyingState>(m_pOwner));
			}
		}
		else if (tag == "Wall")
		{
			std::cout << "Wall\n";

			if (m_pOwner->HasComponent<BlockCollisionCheckComponent>())
			{
				m_pOwner->GetComponent<BlockCollisionCheckComponent>()->SetHitBlock(true);
			}
			if (m_pOwner->HasComponent<MovementComponent>())
			{
				m_pOwner->GetComponent<MovementComponent>()->SetHitWall(true);
			}
		}
	}
}
