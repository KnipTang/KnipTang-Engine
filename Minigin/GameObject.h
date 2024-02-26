#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "Component.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		void AddComponent(Component* component);

		void RemoveComponent(Component* component);

		template<typename T>
		T* GetComponent() const {
			for (const auto& component : m_pComponents) {
				if (T* derived = dynamic_cast<T*>(component.get())) {
					return derived;
				}
			}
			return nullptr;
		}
		
		template<typename T>
		bool HasComponent() const {
			return GetComponent<T>() != nullptr;
		}

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		std::vector<std::unique_ptr<Component>> m_pComponents;
	};
}
