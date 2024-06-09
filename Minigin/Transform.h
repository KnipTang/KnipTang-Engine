#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		Transform(GameObject* gameObject) : Component(gameObject) { m_WorldPosition = { 0,0,0 }; m_LocalPosition = { 0,0,0 }; }
		~Transform() override = default;

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		void Update(float /*deltaTime*/) override {}
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		//const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetWorldPosition(float x, float y, float z);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(glm::vec3 pos);
		const glm::vec3 GetWorldPosition();

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3 GetLocalPosition() const { return m_LocalPosition; }

		void SetPositionDirty();

	private:
		void UpdateWorldPosition();

		glm::vec3 m_WorldPosition{0,0,0};
		glm::vec3 m_LocalPosition{0,0,0};



		bool m_PositionIsDirty = false;
	};
}
