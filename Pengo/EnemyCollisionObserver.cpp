#include "EnemyCollisionObserver.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "Component.h"
#include "WallMovementComponent.h"
#include "WallComponent.h"
#include "EnemyMovementAIComponent.h"
#include "MovementComponent.h"
#include "ScoreComponent.h"

void EnemyCollisionObserver::NotifyCollision(dae::GameCollisionEvent event, dae::CollisionComponent* actor)
{
	if (event == dae::GameCollisionEvent::Collision)
	{
		std::string layer = actor->GetOwner()->GetLayer();

		if (layer == "Player")
		{
			if (m_pOwner->GetTag() == "PlayableEnemy")
				m_pOwner->SetGameObjectPosition(200, 264);
		}
		if (layer == "Enemy")
		{
			
		}
		if (layer == "Wall")
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
					dae::Scene* statsScene = dae::SceneManager::GetInstance().GetSceneByName("GameStats");
					dae::GameObject* score = statsScene->GetGameObjectWithLayer("Score");
					score->GetComponent<ScoreComponent>()->AddScore(500);

					m_pOwner->GetComponent<EnemyComponent>()->Dies();
				}
			}
			else
			{
				std::string tag = actor->GetOwner()->GetTag();
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

					if (m_pOwner->GetTag() == "PlayableEnemy")
						m_pOwner->GetComponent<MovementComponent>()->StunForSeconds(0.1f);
					else
						actor->GetOwner()->SetParent(m_pOwner, true);
				}
			}
		}
	}
}
