#include "PengoCollisionObserver.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "PengoComponent.h"

void PengoCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string layer = actor->GetOwner()->GetLayer();
		
		if (layer == "Player")
		{
		}
		else if (layer == "Enemy")
		{

			m_pOwner->SetGameObjectPosition(actor->GetOwner()->GetGameObjectPosition().x, actor->GetOwner()->GetGameObjectPosition().y);

			if (m_pOwner->HasComponent<PengoComponent>())
			{
				if(!m_pOwner->GetComponent<PengoComponent>()->IsPengoKilled())
				{
					m_pOwner->GetComponent<PengoComponent>()->SetPengoIsKilled(true);
					actor->GetOwner()->SetGameObjectPosition(200, 264);
				}
			}
		}
		else if (layer == "Wall")
		{
			if (m_pOwner->HasComponent<MovementComponent>())
			{
				m_pOwner->GetComponent<MovementComponent>()->SetHitWall(true);
			}
		}
	}
}
