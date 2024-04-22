#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include "GameObject.h"

namespace dae
{
	class RotationComponent final : public Component
	{
	public:
		void Update(float deltaTime) override;
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		RotationComponent(GameObject* gameObject) : Component(gameObject) { }
		~RotationComponent() override {}
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;
	private:
		glm::vec3 m_Velocity{30,25,0};

		//GameObject* m_CenterRotationObject{};

		float m_Angle{ };
		float m_AngularSpeed{ 2.f };
		float m_Radius{ 50.f };
		glm::vec3 m_Center{200,200,50 };
	};
}
