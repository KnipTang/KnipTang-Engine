#pragma once

namespace dae
{
	class Texture2D;
	class Renderer;
	class GameObject;

	class Component
	{
	public:
		virtual void Update(const GameObject& gameObject, float deltaTime) = 0;
		virtual void LateUpdate(const GameObject& gameObject, float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void Render(const GameObject& gameObject) const = 0;

		//Component(/*GameObject* pParent*/) : /*m_pParent(pParent)*/ {};
		Component() = default;
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		//dae::GameObject* m_pParent{};
	};
}
