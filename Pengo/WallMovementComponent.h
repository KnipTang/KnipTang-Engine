#pragma once
#include <Component.h>
#include "GameObject.h"
class WallMovementComponent : public dae::Component
{
public:
	void Update(float deltaTime) override;
	void LateUpdate(float) override;
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	void Move(glm::vec3 direction);

	void SetDirection(glm::vec3 direction) { m_Direction = direction; }
	glm::vec3 GetDirection() { return m_Direction; }

	void SetHitWall(bool hit) { m_HitWall = hit; }

	WallMovementComponent(dae::GameObject* gameObject) : dae::Component(gameObject) { };
	virtual ~WallMovementComponent() { }
	WallMovementComponent(const WallMovementComponent& other) = delete;
	WallMovementComponent(WallMovementComponent&& other) = delete;
	WallMovementComponent& operator=(const WallMovementComponent& other) = delete;
	WallMovementComponent& operator=(WallMovementComponent&& other) = delete;

private:
	//void StopMoving();
	glm::vec3 m_Direction;
	float m_Speed;

	bool m_HitWall = false;

	bool m_Moving = false;
	float m_TraveledLength = 0;

	glm::vec3 m_StartPos;
};

