#pragma once
#include <iostream>
#include "GameObject.h"

namespace dae
{
	class Command {
	public:
		Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute(float deltaTime) = 0;
	};

	class GameActorCommand : public Command {
		GameObject* m_actor;
	protected:
		GameObject* GetGameObject() const { return m_actor; }
	public:
		GameActorCommand(GameObject* actor) : m_actor{ actor } {}
		virtual ~GameActorCommand() = default;

		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other) = delete;
	};
}