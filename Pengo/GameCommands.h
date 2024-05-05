#pragma once
#include <iostream>
#include "Command.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
	class JumpCommand : public GameActorCommand {
	public:
		JumpCommand(GameObject* actor) : GameActorCommand(actor) {}
	
		void Execute(float /*deltaTime*/) override
		{
			std::cout << "Jump";
		}
	};
	
	class FireCommand : public GameActorCommand {
	public:
		FireCommand(GameObject* actor) : GameActorCommand(actor) {}
	
		void Execute(float /*deltaTime*/) override
		{
			std::cout << "Fire";
		}
	};
	
	class Damage : public GameActorCommand {
	public:
		Damage(GameObject* actor, HealthComponent* healthComponent) : GameActorCommand(actor), m_HealthComponent(healthComponent) {}
	
		void Execute(float /*deltaTime*/) override
		{
			m_HealthComponent->DamageLives(1);
		}
	private:
		HealthComponent* m_HealthComponent;
	};
	
	class PointIncrease : public GameActorCommand {
	public:
		PointIncrease(GameObject* actor, ScoreComponent* pointsComponent) : GameActorCommand(actor), m_PointsComponent(pointsComponent) {}
	
		void Execute(float /*deltaTime*/) override
		{
			m_PointsComponent->AddPoints(100);
		}
	private:
		ScoreComponent* m_PointsComponent;
	};
}