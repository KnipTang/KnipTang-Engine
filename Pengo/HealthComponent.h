#pragma once
#include "Component.h"
#include "Subject.h"
#include "StateDisplay.h"
#include "ResourceManager.h"
#include "TextObject.h"
namespace dae
{
	class HealthComponent : public Component, public Subject
	{
	public:
		void Update(float /*deltaTime*/) override { }
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		double GetHealth() { return m_CurrentHealth; }
		void SetHealth(double health) { m_CurrentHealth = health; }

		void AddHealth(double health) { m_CurrentHealth += health; }
		void DecreaseHealth(double health);

		int GetLives() { return m_CurrentLives; }
		void SetLives(int lives) { m_CurrentLives = lives; }

		void AddLives(int lives) { m_CurrentLives += lives; }
		void DamageLives(int lives);

		void Die();

		HealthComponent(GameObject* gameObject) : Component(gameObject), Subject(gameObject) { }
		virtual ~HealthComponent() { }
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:
		double m_CurrentHealth = 5;

		int m_CurrentLives = 3;
		int m_StartLives = 3;
	};
}
