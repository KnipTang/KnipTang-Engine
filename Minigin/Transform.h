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
		void Render(const GameObject& /*gameObject*/) const override {}

		const glm::vec3& GetPosition() const { return m_position; }

		void SetPosition(float x, float y, float z);
		void SetPosition(float x, float y);

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition() const { return m_LocalPos; }
		const glm::vec3 GetWorldPosition() const;
		void SetPositionDirty();

		explicit Transform(GameObject* pParent) : Component(pParent) {}
		~Transform() override = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;
	private:
		glm::vec3 m_position{};
		glm::vec3 m_LocalPos{};
	};
}
