#pragma once
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
	~StartGameCommand() override = default;

	StartGameCommand(const StartGameCommand& other) = delete;
	StartGameCommand(StartGameCommand&& other) = delete;
	StartGameCommand& operator=(const StartGameCommand& other) = delete;
	StartGameCommand& operator=(StartGameCommand&& other) = delete;

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

class NextLevel : public dae::Command {
public:
	NextLevel(dae::Scene* scene, std::vector<std::unique_ptr<Level>> levelLayouts)
		: Command(), m_Scene(scene), m_LevelLayouts(std::move(levelLayouts))
	{

	}
	~NextLevel() override = default;

	NextLevel(const NextLevel& other) = delete;
	NextLevel(NextLevel&& other) = delete;
	NextLevel& operator=(const NextLevel& other) = delete;
	NextLevel& operator=(NextLevel&& other) = delete;

	void Execute(float /*deltaTime*/) override
	{
		m_CurrentLevelIndex = (m_CurrentLevelIndex + 1) % m_LevelLayouts.size();

		m_Scene->RemoveAll();
		
		auto level = m_LevelLayouts.at(m_CurrentLevelIndex)->LoadLevel();
		
		for (auto& object : level)
		{
			m_Scene->Add(std::move(object));
		}

		std::vector<dae::GameObject*> enemyWalls = m_Scene->GetGameObjectsWithTag("EnemyWall");

		if (m_EnemiesSpawnAtStart > enemyWalls.size())
			m_EnemiesSpawnAtStart = enemyWalls.size();

		for (size_t i = 0; i < m_EnemiesSpawnAtStart; i++)
		{
			enemyWalls.at(i)->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
		}
	}
private:
	int m_CurrentLevelIndex = 0;
	std::vector<std::unique_ptr<Level>> m_LevelLayouts;
	dae::Scene* m_Scene;

	size_t m_EnemiesSpawnAtStart = 3;
};