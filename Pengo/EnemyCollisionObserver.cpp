#include "EnemyCollisionObserver.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "Component.h"

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
			if (m_pOwner->GetParent() != actor->GetOwner())
			{
				m_pOwner->GetComponent<EnemyComponent>()->Dies();
			}
		}
	}
}
