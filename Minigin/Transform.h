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

		//const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(glm::vec3 pos) { m_WorldPosition = pos; }
		const glm::vec3 GetWorldPosition();

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3 GetLocalPosition() const { return m_LocalPosition; }

		void SetPositionDirty();

		Transform(GameObject* gameObject) : Component(gameObject) {}
	private:
		void UpdateWorldPosition();

		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};



		bool m_PositionIsDirty = false;
	};
}
