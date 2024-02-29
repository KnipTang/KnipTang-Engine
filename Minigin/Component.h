#pragma once
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Texture2D;
	class Renderer;

	class Component
	{
		std::unique_ptr<GameObject> m_pOwner;
	public:
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void FixedUpdate(float fixedTimeStep) = 0;
		virtual void Render() const = 0;

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

	protected:
		explicit Component(GameObject* owner) : m_pOwner(owner) {}
		GameObject* GetOwner() const { return m_pOwner.get(); }
	};
}
