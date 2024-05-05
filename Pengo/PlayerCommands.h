#pragma once
#include <iostream>
#include "Command.h"

namespace dae
{
	class Movement : public GameActorCommand {
	public:
		Movement(GameObject* actor, glm::vec3 direction, float speed = 16.f) : GameActorCommand(actor), m_Direction(direction), m_Speed(speed) { }

		void Execute(float /*deltaTime*/) override
		{
			glm::vec3 objPos = GetGameObject()->GetTransform()->GetWorldPosition();
			objPos += m_Direction * m_Speed;
			GetGameObject()->SetGameObjectPosition(objPos.x, objPos.y);
		}
	private:
		glm::vec3 m_Direction;
		float m_Speed;
	};
}