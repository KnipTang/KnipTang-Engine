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
namespace dae
{
	class Movement : public GameActorCommand {
	public:
		Movement(GameObject* actor, Controlls control) : GameActorCommand(actor), m_Control(control)
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

	class Attack : public GameActorCommand {
	public:
		Attack(GameObject* actor, Controlls control) : GameActorCommand(actor), m_Control(control)
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

	class StartGame : public GameActorCommand {
	public:
		StartGame(GameObject* actor) : GameActorCommand(actor)
		{
		}

		void Execute(float /*deltaTime*/) override
		{
			dae::SceneManager::GetInstance().UnloadScene("StartScreen");
			dae::Scene& currentScene = dae::SceneManager::GetInstance().LoadScene("Demo");

			std::vector<dae::GameObject*> enemyWalls = currentScene.GetGameObjectsWithTag("EnemyWall");
			
			for (int i = 0; i < m_EnemiesSpawnAtStart; i++)
			{
				enemyWalls.at(i)->GetComponent<EnemySpawnComponent>()->SpawnEnemy();
			}
		}
	private:
		int m_EnemiesSpawnAtStart = 3;
	};
}