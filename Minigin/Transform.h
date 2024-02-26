#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		void Update(const GameObject& /*gameObject*/, float /*deltaTime*/) override {};
		void LateUpdate(const GameObject& /*gameObject*/, float /*deltaTime*/) override {};
		void FixedUpdate(float /*fixedTimeStep*/) override {};
		void Render(const GameObject& /*gameObject*/) const override {};

		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z);
		void SetPosition(float x, float y);
	private:
		glm::vec3 m_position{};
	};
}
