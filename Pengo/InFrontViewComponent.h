#pragma once
#include <Component.h>
#include "glm/glm.hpp"
class InFrontViewComponent : public dae::Component
{
public:
	InFrontViewComponent(dae::GameObject* gameObject) : Component(gameObject) { }
	~InFrontViewComponent() override = default;

	InFrontViewComponent(const InFrontViewComponent& other) = delete;
	InFrontViewComponent(InFrontViewComponent&& other) = delete;
	InFrontViewComponent& operator=(const InFrontViewComponent& other) = delete;
	InFrontViewComponent& operator=(InFrontViewComponent&& other) = delete;

	void UpdatePosition(glm::vec3 direction);
};
