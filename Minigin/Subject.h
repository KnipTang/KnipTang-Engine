#pragma once
#include <iostream>
#include <vector>
#include "Component.h"
#include "Observer.h"
namespace dae
{
	//SUBJECT
	class Subject
	{
	public:
		void AddObserver(Observer* observer) {
			m_observers.push_back(std::unique_ptr<Observer>(observer));
		}
		void RemoveObserver(Observer* observer) {
			auto it = std::find_if(m_observers.begin(), m_observers.end(),
				[&observer](const std::unique_ptr<Observer>& ptr) { return ptr.get() == observer; });

			if (it != m_observers.end()) {
				m_observers.erase(it);
			}
		}

		GameObject* GetGameObject() { return m_GameObject; }

		Subject(GameObject* gameObject) : m_GameObject(gameObject) {}
		virtual ~Subject() {}
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void NotifyObservers(GameEvent event) {
			for (const auto& observer : m_observers)
				observer->Notify(event, this);
		}
	private:
		std::vector<std::unique_ptr<Observer>> m_observers;
		GameObject* m_GameObject;
	};
}