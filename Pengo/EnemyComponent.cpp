#include "EnemyComponent.h"
#include "GameConfig.h"
#include "EnemyCollisionObserver.h"
#include "CollisionComponent.h"
#include "Animation.h"
#include <Scene.h>
#include "EnemySpawnComponent.h"

EnemyComponent::EnemyComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{

}

void EnemyComponent::Update(float)
{
	if (m_State != nullptr)
		m_State->Update();
}

void EnemyComponent::SetHitByWallPos(glm::vec3 direction)
{
	GetOwner()->SetGameObjectPosition(direction.x * Config::ELEMENT_SIZE, direction.y * Config::ELEMENT_SIZE);

	m_WasHitByWall = true;
}

void EnemyComponent::Dies()
{
	dae::GameObject* enemyWalls = GetEnemySpawnBlock();
	if (enemyWalls != nullptr)
	{
		if(enemyWalls->HasComponent<EnemySpawnComponent>())
			enemyWalls->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
	}

	GetOwner()->RemoveGameObject();
}

dae::GameObject* EnemyComponent::GetEnemySpawnBlock()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetSceneByName("Demo");
	std::vector<dae::GameObject*> enemyWalls = currentScene->GetGameObjectsWithTag("EnemyWall");

	if (enemyWalls.size() >= 1)
		return enemyWalls.at(0);

	return nullptr;
}
