#pragma once
#include <iostream>
#include "GameObject.h"

namespace dae
{
	class Command {
	public:
		virtual ~Command() = default;
		virtual void Execute(float deltaTime) = 0;
	};

	class GameActorCommand : public Command {
		GameObject* m_actor;
	protected:
		GameObject* GetGameObject() const { return m_actor; }
	public:
		GameActorCommand(GameObject* actor) : m_actor{ actor } {}
		virtual ~GameActorCommand() {}
	};
}