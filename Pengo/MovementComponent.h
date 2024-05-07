#pragma once
#include "Component.h"
#include "GameObject.h"

class MovementComponent : public dae::Component
{
public:
	void Update(float /*deltaTime*/) override {}
	void LateUpdate(float /*deltaTime*/) override;
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	void SetDirection(glm::vec3 direction) { m_Direction = direction; }

	void SetHitWall(bool hit) { m_HitWall = hit; }

	MovementComponent(dae::GameObject* gameObject, float speed = 16.f) : dae::Component(gameObject), m_Speed(speed) { };
	virtual ~MovementComponent() { }
	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;

private:
	glm::vec3 m_Direction;
	float m_Speed;

	bool m_HitWall = false;
};
