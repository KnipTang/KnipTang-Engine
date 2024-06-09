#pragma once

namespace dae
{
	class Texture2D;
	class Renderer;
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* gameObject) : m_pOwner(gameObject) {}
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float) {}
		virtual void LateUpdate(float) {}
		virtual void FixedUpdate(float) {}
		virtual void Render() const {}

		GameObject* GetOwner() const { return m_pOwner; }

		bool IsRemoveComponentTrue() { return m_RemoveComponent; }
		void RemoveComponent() { m_RemoveComponent = true; }
	private:
		GameObject* m_pOwner;

		bool m_RemoveComponent = false;
	};
}
