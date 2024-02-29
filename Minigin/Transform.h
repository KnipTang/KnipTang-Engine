#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		void Update(float /*deltaTime*/) override {}
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		void SetPosition(float x, float y, float z);
		void SetPosition(float x, float y);

		//Position
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3 GetWorldPosition();
		void UpdateWorldPosition();
		void SetPositionDirty() { m_PositionIsDirty = true; }

		//Rotation
		void SetRotationPosition(const glm::vec3& rotation) { m_RotationPosition = rotation; }
		const glm::vec3& GetRotationPosition() const { return m_RotationPosition; }

		Transform(GameObject* owner) : Component(owner) {}
		~Transform() override = default;

	private:
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_RotationPosition{};

		bool m_PositionIsDirty = false;
	};
}
