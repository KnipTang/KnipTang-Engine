#include "InFrontObserver.h"
#include "CollisionComponent.h"
#include "AttackComponent.h"
#include "PengoComponent.h"

void InFrontObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string layer = actor->GetOwner()->GetLayer();

		if (layer == "Player")
		{
		}
		else if (layer == "Enemy")
		{
		}
		else if (layer == "Wall")
		{
			if (m_pOwner->GetParent() == nullptr)
				return;

			if (m_pOwner->GetParent()->HasComponent<MovementComponent>())
			{
				m_pOwner->GetParent()->GetComponent<MovementComponent>()->SetHitWall(true);
			}
			if (m_pOwner->GetParent()->HasComponent<AttackComponent>())
			{
				m_pOwner->GetParent()->GetComponent<AttackComponent>()->SetInfrontObject(actor->GetOwner());
				m_pOwner->GetParent()->GetComponent<AttackComponent>()->SetAttackReady(true);
			}
		}
	}
	

}

