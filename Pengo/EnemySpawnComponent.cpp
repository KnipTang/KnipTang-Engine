#include "EnemySpawnComponent.h"
#include "EnemyComponent.h"
#include "RenderComponent.h"
#include "EnemyMovementAIComponent.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "EnemyCollisionObserver.h"
#include "GameObject.h"
#include "Animation.h"
#include "WallComponent.h"

void EnemySpawnComponent::Update(float)
{
    if (m_EnemyAni == nullptr)
    {
        GetOwner()->AddComponent(new EnemyMovementAIComponent(GetOwner()));
        GetOwner()->RemoveComponent(this);
        return;
    }

    if (!m_EnemyAni->IsAnimating())
    {
        SDL_Rect startEnemyRect = { 0, 16 * 9, 16, 16 };

        m_EnemyAni->ToggleAnimation(true);
        m_EnemyAni->SetStartSourceRect(startEnemyRect);

        GetOwner()->AddComponent(new EnemyMovementAIComponent(GetOwner()));
        GetOwner()->RemoveComponent(this);
    }
    //if (!m_AnimationDone)
    //{
    //    m_CurrentTimer += deltaTime;
    //
    //    if (m_CurrentTimer >= 5)
    //    {
    //        ReplaceWallWithEnemy();
    //        m_CurrentTimer = 0;
    //    }
    //}

   // if (m_AnimationDone)
   // {
   //     m_CurrentTimer += deltaTime;
   //
   //     if (m_CurrentTimer >= m_AnimationTime)
   //         ReplaceWallWithEnemy();
   // }


}

void EnemySpawnComponent::SpawnEnemy()
{
    //WallComponent* wallComp = GetOwner()->GetComponent<WallComponent>();
    //
    //if (wallComp != nullptr)
    //    wallComp->PlayBreakWall();
    //
    //m_AnimationDone = true;
    //m_AnimationTime = wallComp->GetTimeToBreakWall();
}

void EnemySpawnComponent::ReplaceWallWithEnemy()
{
    //glm::vec2 posWall = GetOwner()->GetGameObjectPosition();
    //
    //auto enemy = std::make_unique<dae::GameObject>();
    //
    //enemy.get()->AddComponent(new EnemyMovementAIComponent(enemy.get()));
    //enemy.get()->AddComponent(new dae::RenderComponent(enemy.get()));
    //enemy.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    //enemy.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 8, 16, 16);
    //enemy.get()->SetGameObjectPosition(static_cast<float>(posWall.x), static_cast<float>(posWall.y));
    //enemy.get()->AddComponent(new Animation(enemy.get(), true, 6));
    //enemy.get()->AddComponent(new EnemyComponent(enemy.get()));
    //enemy.get()->AddComponent(new dae::CollisionComponent(enemy.get(), 16.f, 16.f));
    //enemy.get()->AddComponent(new dae::HealthComponent(enemy.get()));
    //enemy.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(enemy.get()));
    //enemy.get()->SetTag("Enemy");
    //
    //dae::SceneManager::GetInstance().GetSceneByName("Demo")->Add(std::move(enemy));

    //GetOwner()->RemoveGameObject();
}
