#pragma once
#include <iostream>
#include "Command.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "PengoPlayer.h"
namespace dae
{
	class Movement : public GameActorCommand {
	public:
		Movement(GameObject* actor, PengoPlayer* player, Controlls control, float speed = 16.f) : GameActorCommand(actor), m_NewControl(control), m_Speed(speed)
		{
			m_Player = player;

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

		void Execute(float /*deltaTime*/) override
		{
			glm::vec3 objPos = GetGameObject()->GetTransform()->GetWorldPosition();
			objPos += m_Direction * m_Speed;
			GetGameObject()->SetGameObjectPosition(objPos.x, objPos.y);

			if (GetGameObject()->HasComponent<MovementComponent>())
			{
				GetGameObject()->GetComponent<MovementComponent>()->SetDirection(m_Direction);
			}

			m_Player->HandleInput(m_NewControl);
		}
	private:
		glm::vec3 m_Direction;
		float m_Speed;

		PengoPlayer* m_Player;
		Controlls m_NewControl;
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