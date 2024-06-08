#include "EnemyComponent.h"
#include "GameConfig.h"
#include "EnemyCollisionObserver.h"
#include "CollisionComponent.h"
#include "Animation.h"
#include <Scene.h>
#include "EnemySpawnComponent.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "SoundServiceLocator.h"

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
	dae::Scene* statsScene = dae::SceneManager::GetInstance().GetSceneByName("GameStats");
	dae::GameObject* score = statsScene->GetGameObjectWithLayer("Score");
	score->GetComponent<ScoreComponent>()->AddScore(500);

	dae::GameObject* enemyWalls = GetEnemySpawnBlock();
	if (enemyWalls != nullptr)
	{
		if (enemyWalls->HasComponent<EnemySpawnComponent>())
			enemyWalls->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
	}
	else
	{
		dae::Scene* currentScene = dae::SceneManager::GetInstance().GetSceneByName("Demo");
		size_t amountEnemies = currentScene->GetGameObjectsWithLayer("Enemy").size();

		if (amountEnemies <= 1)
		{
			dae::SceneManager::GetInstance().UnloadScene("Demo");
			dae::SceneManager::GetInstance().LoadScene("EndScene");
		}
	}

	dae::SoundServiceLocator::get_sound_system().play("Snow-BeeSquashed.mp3", 10);

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
