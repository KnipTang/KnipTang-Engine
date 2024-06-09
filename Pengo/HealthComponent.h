#pragma once
#include "Component.h"
#include "StateDisplay.h"
#include "Subject.h"
#include "TextObject.h"

class HealthComponent : public dae::Component
{
public:
	HealthComponent(dae::GameObject* gameObject, int startLives = 1) : Component(gameObject), m_StartLives(startLives)
	{
		m_CurrentLives = m_StartLives;
	}
	~HealthComponent() override = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	int GetCurrentLives() { return m_CurrentLives; }
	void SetCurrentLives(int lives) { m_CurrentLives = lives; }

	int AddLives(int lives = 1) { m_CurrentLives += lives; return m_CurrentLives; }
	int DamageLives(int lives = 1);

	void Die();

	void AddObserver(StateDisplay* observer) {
		m_observers.push_back(std::unique_ptr<StateDisplay>(observer));
	}
	void RemoveObserver(StateDisplay* observer) {
		auto it = std::find_if(m_observers.begin(), m_observers.end(),
			[&observer](const std::unique_ptr<StateDisplay>& ptr) { return ptr.get() == observer; });

		if (it != m_observers.end()) {
			m_observers.erase(it);
		}
	}

	void NotifyObservers(PengoEvents event) {
		for (const auto& observer : m_observers)
			observer->Notify(event, this);
	}


private:
	int m_CurrentLives;
	int m_StartLives;

	std::vector<std::unique_ptr<StateDisplay>> m_observers;
};
