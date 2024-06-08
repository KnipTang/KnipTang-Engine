#pragma once
#include <iostream>
#include "Command.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "PengoComponent.h"
#include "PengoState.h"
#include "AttackComponent.h"
#include "EnemySpawnComponent.h"
#include "Scene.h"
#include "Level.h"

class Movement : public dae::GameActorCommand {
public:
	Movement(dae::GameObject* actor, Controlls control) : GameActorCommand(actor), m_Control(control)
	{
		switch (control)
		{
		case Controlls::UP:
			m_Direction = glm::vec3(0, -1, 0);
			break;
		case Controlls::DOWN:
			m_Direction = glm::vec3(0, 1, 0);
			break;
		case Controlls::LEFT:
			m_Direction = glm::vec3(-1, 0, 0);
			break;
		case Controlls::RIGHT:
			m_Direction = glm::vec3(1, 0, 0);
			break;
		default:
			std::cout << "Unknown control" << std::endl;
			m_Direction = glm::vec3(0, 0, 0);
			break;
		}
	}

	void Execute(float deltaTime) override
	{
		PengoComponent* pengoComp = GetGameObject()->GetComponent<PengoComponent>();
		if (pengoComp != nullptr)
		{
			if (pengoComp->IsPengoKilled())
				return;

			pengoComp->HandleInput(m_Control);
		}
		if (GetGameObject()->HasComponent<PengoComponent>())
		{
			GetGameObject()->GetComponent<PengoComponent>()->SetCurrentDirection(m_Direction);
		}
		if (GetGameObject()->HasComponent<MovementComponent>())
		{
			GetGameObject()->GetComponent<MovementComponent>()->Move(deltaTime, m_Direction);
		}
		if (GetGameObject()->HasComponent<AttackComponent>())
		{
			GetGameObject()->GetComponent<AttackComponent>()->JoyStickPressed();
		}
	}
private:
	glm::vec3 m_Direction{0,0,0};

	Controlls m_Control;
};

class Attack : public dae::GameActorCommand {
public:
	Attack(dae::GameObject* actor, Controlls control) : GameActorCommand(actor), m_Control(control)
	{
	}

	void Execute(float /*deltaTime*/) override
	{
		if (GetGameObject()->HasComponent<AttackComponent>())
		{
			GetGameObject()->GetComponent<AttackComponent>()->Attack();
		}
		if (GetGameObject()->HasComponent<PengoComponent>())
		{
			GetGameObject()->GetComponent<PengoComponent>()->HandleInput(Controlls::ATTACK);
		}
	}
private:
	Controlls m_Control;
};

class StartGame : public dae::GameActorCommand {
public:
	StartGame(dae::GameObject* actor) : GameActorCommand(actor)
	{
	}

	void Execute(float /*deltaTime*/) override
	{
		dae::SceneManager::GetInstance().UnloadScene("StartScreen");
		dae::Scene* currentScene = dae::SceneManager::GetInstance().LoadScene("Demo");

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
};

class SkipLevel : public dae::GameActorCommand {
public:
	SkipLevel(dae::GameObject* actor, std::vector<dae::GameObject*> level) : GameActorCommand(actor), m_Level(level)
	{
		m_LevelLayouts =
		{
			{ "Resources/Level1.txt" },
			{ "Resources/Level2.txt" },
		};
	}

	void Execute(float /*deltaTime*/) override
	{
		m_CurrentLevelIndex++;

		m_Level.clear();
		auto level = m_LevelLayouts.at(m_CurrentLevelIndex).LoadLevel();

		for (auto& object : level)
		{
			m_Level.emplace_back(object.get());
		}
	}
private:
	int m_CurrentLevelIndex = 0;
	std::vector<Level> m_LevelLayouts;
	std::vector<dae::GameObject*> m_Level;
};
