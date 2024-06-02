#include "EnemySpawnComponent.h"
#include "EnemyComponent.h"
#include "RenderComponent.h"
#include "EnemyMovementAIComponent.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "EnemyCollisionObserver.h"
#include "GameObject.h"

void EnemySpawnComponent::SpawnEnemy()
{

    glm::vec2 posWall = GetOwner()->GetGameObjectPosition();

    auto enemy = std::make_unique<dae::GameObject>();

    enemy.get()->AddComponent(new EnemyComponent(enemy.get()));
    enemy.get()->AddComponent(new EnemyMovementAIComponent(enemy.get()));
    enemy.get()->AddComponent(new dae::RenderComponent(enemy.get()));
    enemy.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    enemy.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 9, 16, 16);
    enemy.get()->SetGameObjectPosition(static_cast<float>(posWall.x), static_cast<float>(posWall.y));
    enemy.get()->AddComponent(new dae::CollisionComponent(enemy.get(), 16.f, 16.f));
    enemy.get()->AddComponent(new dae::HealthComponent(enemy.get()));
    enemy.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(enemy.get()));
    enemy.get()->SetTag("Enemy");

    dae::SceneManager::GetInstance().GetSceneByName("Demo")->Add(std::move(enemy));

    GetOwner()->RemoveGameObject();
}
