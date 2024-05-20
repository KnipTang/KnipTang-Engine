#include "InFrontObserver.h"
#include "CollisionComponent.h"
#include <iostream>
#include "InFrontViewComponent.h"
#include "AttackComponent.h"
#include "PengoComponent.h"

void InFrontObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string tag = actor->GetOwner()->GetTag();
		//std::cout << "Begin OverLapping: " << m_pOwner->GetTag() << " With: ";

		if (tag == "Player")
		{
			std::cout << "Player\n";
		}
		else if (tag == "Enemy")
		{
			std::cout << "Enemy\n";
		}
		else if (tag == "Wall")
		{
			if (m_pOwner->GetParent()->HasComponent<AttackComponent>())
			{
				m_pOwner->GetParent()->GetComponent<AttackComponent>()->SetInfrontObject(actor->GetOwner());
				m_pOwner->GetParent()->GetComponent<AttackComponent>()->SetAttackReady(true);
			}
		}
	}
	

}

