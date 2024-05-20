#pragma once
#include <Component.h>
#include "glm/glm.hpp"
class InFrontViewComponent : public dae::Component
{
public:
	void Update(float ) override {};
	void LateUpdate(float ) override {};
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	void UpdatePosition(glm::vec3 direction);

	InFrontViewComponent(dae::GameObject* gameObject) : dae::Component(gameObject) { };
	virtual ~InFrontViewComponent() { }
	InFrontViewComponent(const InFrontViewComponent& other) = delete;
	InFrontViewComponent(InFrontViewComponent&& other) = delete;
	InFrontViewComponent& operator=(const InFrontViewComponent& other) = delete;
	InFrontViewComponent& operator=(InFrontViewComponent&& other) = delete;
private:
};

