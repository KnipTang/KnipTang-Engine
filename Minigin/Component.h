#pragma once
#include <memory>

namespace dae
{
	class Texture2D;
	class Renderer;
	class GameObject;

	class Component
	{
		std::unique_ptr<GameObject> m_pOwner;
	public:
		virtual void Update(const GameObject& gameObject, float deltaTime) = 0;
		virtual void LateUpdate(const GameObject& gameObject, float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void Render(const GameObject& gameObject) const = 0;

		//Component(/*GameObject* pParent*/) : /*m_pOwner(pParent)*/ {};
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		explicit Component(GameObject* pParent) : m_pOwner(pParent) {}
		GameObject* GetOwner() const { return m_pOwner.get(); }
	};
}
