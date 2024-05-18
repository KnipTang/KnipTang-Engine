#pragma once
#include <iostream>
#include "Command.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "PengoComponent.h"
#include "PengoState.h"
namespace dae
{
	class Movement : public GameActorCommand {
	public:
		Movement(GameObject* actor, Controlls control) : GameActorCommand(actor), m_Control(control)
		{
			switch (control)
			{
			case Controlls::UP:
				std::cout << "UP" << std::endl;
				m_Direction = glm::vec3(0, -1, 0);
				break;
			case Controlls::DOWN:
				std::cout << "DOWN" << std::endl;
				m_Direction = glm::vec3(0, 1, 0);
				break;
			case Controlls::LEFT:
				std::cout << "LEFT" << std::endl;
				m_Direction = glm::vec3(-1, 0, 0);
				break;
			case Controlls::RIGHT:
				std::cout << "RIGHT" << std::endl;
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
			std::cout << "Moving\n";
			if (GetGameObject()->HasComponent<PengoComponent>())
			{
				GetGameObject()->GetComponent<PengoComponent>()->HandleInput(m_Control);
			}

			if (GetGameObject()->HasComponent<MovementComponent>())
			{
				GetGameObject()->GetComponent<MovementComponent>()->Move(deltaTime, m_Direction);
			}

		}
	private:
		glm::vec3 m_Direction;

		Controlls m_Control;
	};

	class Attack : public GameActorCommand {
	public:
		Attack(GameObject* actor) : GameActorCommand(actor) { }

		void Execute(float /*deltaTime*/) override
		{
			std::cout << "Attacking\n";
			GetGameObject()->GetTransform()->SetLocalPosition(glm::vec3{ 5,5,5 });
			if (GetGameObject()->HasComponent<PengoComponent>())
			{
				GetGameObject()->GetComponent<PengoComponent>()->HandleInput(Controlls::ATTACK);
			}
		}
	private:
	};

	//class SetControlState : public GameActorCommand {
	//public:
	//	SetControlState(GameObject* actor, PengoPlayer* player, Controlls control) : GameActorCommand(actor), m_Player(player), m_NewControl(control) {}
	//
	//	void Execute(float /*deltaTime*/) override
	//	{
	//		m_Player->HandleInput(m_NewControl);
	//	}
	//private:
	//	PengoPlayer* m_Player;
	//
	//	Controlls m_NewControl;
	//};
}