#pragma once

namespace dae
{
	class Texture2D;
	class Renderer;
	class GameObject;

	class Component
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void Render() const = 0;

		GameObject* GetOwner() const { return m_pOwner; }

		//Component(/*GameObject* pParent*/) : /*m_pOwner(pParent)*/ {};
		Component(GameObject* gameObject) : m_pOwner(gameObject) {}
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	private:
		GameObject* m_pOwner;
	};
}
