#pragma once
#include <iostream>
#include "Command.h"
#include "SceneManager.h"
#include "Level.h"
#include "EnemySpawnComponent.h"

enum class GameModes
{
	Single,
	CoOp,
	Versus
};

class StartGameCommand : public dae::Command
{
public:
	StartGameCommand(GameModes mode) : Command(), m_GameMode(mode) {}

	void Execute(float /*deltaTime*/) override
	{
		dae::SceneManager::GetInstance().UnloadScene("StartScreen");
		dae::SceneManager::GetInstance().LoadScene("GameStats");
		dae::SceneManager::GetInstance().LoadScene("GameLayout");
		dae::Scene* currentScene = dae::SceneManager::GetInstance().LoadScene("LevelScene");

		if (m_GameMode == GameModes::CoOp)
		{
			Level levelCoOp{ "Resources/CoOp.txt" };
			std::vector<std::unique_ptr<dae::GameObject>> level = levelCoOp.LoadLevel();

			for (auto& object : level)
			{
				currentScene->Add(std::move(object));
			}
		}
		else if (m_GameMode == GameModes::Versus)
		{
			Level levelCoOp{ "Resources/Versus.txt" };
			std::vector<std::unique_ptr<dae::GameObject>> level = levelCoOp.LoadLevel();

			for (auto& object : level)
			{
				currentScene->Add(std::move(object));
			}
		}

		std::vector<dae::GameObject*> enemyWalls = currentScene->GetGameObjectsWithTag("EnemyWall");

		if (m_EnemiesSpawnAtStart > enemyWalls.size())
			m_EnemiesSpawnAtStart = enemyWalls.size();

		for (size_t i = 0; i < m_EnemiesSpawnAtStart; i++)
		{
			enemyWalls.at(i)->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
		}
	}
private:
	size_t m_EnemiesSpawnAtStart = 3;
	GameModes m_GameMode;
};