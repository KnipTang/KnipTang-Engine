#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "Component.h"
#include <string>
namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void FixedUpdate(float fixedTimeStep);
		void Render() const;

		void AddComponent(Component* component);

		void RemoveComponent(Component* component);

		void RemoveAllComponent();

		template<typename T>
		T* GetComponent() const {
			for (const auto& component : m_pComponents) {
				if (T* derived = dynamic_cast<T*>(component.get())) {
					return derived;
				}
			}
			for (const auto& component : m_pPendingComponents) {
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

		GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* parent, bool keepWorldPosition);
		size_t GetChildCount() const { return m_pChildren.size(); }
		GameObject* GetChildAt(unsigned int index) const { return m_pChildren.at(index); }

		void RemoveAllChildren();

		void RemoveGameObject();
		bool IsRemoveGameObjectTrue() { return m_RemoveGameObject; }

		void SetGameObjectPosition(float posX, float posY) { return m_Transform.SetWorldPosition(posX, posY); }
		glm::vec3 GetGameObjectPosition() { return m_Transform.GetWorldPosition(); }

		Transform* GetTransform() { return &m_Transform; }

		void SetTag(std::string tag) { m_Tag = tag; }
		std::string GetTag() { return m_Tag; }

		void SetLayer(std::string layer) { m_Layer = layer; }
		std::string GetLayer() { return m_Layer; }

	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		bool IsChild(GameObject* potentialChild) const;

		std::vector<std::unique_ptr<Component>> m_pComponents;
		std::vector<std::unique_ptr<Component>> m_pPendingComponents;

		Transform m_Transform{this}; //Local transform

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		bool m_RemoveGameObject = false;

		std::string m_Tag = "None";
		std::string m_Layer = "None";
	};
}
