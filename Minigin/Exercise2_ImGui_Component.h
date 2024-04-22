#pragma once
#include "Component.h"
#include <vector>
namespace dae
{
	class Exercise2_ImGui_Component : public Component
	{
	public:
		void Update(float /*deltaTime*/) override {};
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override;

		void CalculateYValuesNormal();
		void CalculateYValuesAlt();

		Exercise2_ImGui_Component(GameObject* gameObject) : Component(gameObject) { CalculateYValuesNormal(); CalculateYValuesAlt(); }
		~Exercise2_ImGui_Component() override {}
		Exercise2_ImGui_Component(const Exercise2_ImGui_Component& other) = delete;
		Exercise2_ImGui_Component(Exercise2_ImGui_Component&& other) = delete;
		Exercise2_ImGui_Component& operator=(const Exercise2_ImGui_Component& other) = delete;
		Exercise2_ImGui_Component& operator=(Exercise2_ImGui_Component&& other) = delete;
	private:
		mutable int m_Samples{ 1 };
		std::vector<float> m_yValuesNormal;
		std::vector<float> m_yValuesAlt;
		const std::vector<float> m_xValues{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
	};
};
