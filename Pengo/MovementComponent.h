#pragma once
#include <chrono>
#include "Component.h"
#include "GameObject.h"
#include "CollisionComponent.h"

class MovementComponent : public dae::Component
{
public:
	MovementComponent(dae::GameObject* gameObject, float speed = 40.f) : Component(gameObject), m_Speed(speed)
	{
		m_HitWall = false;
		m_Moving = false;
		m_Stunned = false;

		m_StunDuration = 0;
	}
	~MovementComponent() override = default;

	MovementComponent(const MovementComponent& other) = delete;
	MovementComponent(MovementComponent&& other) = delete;
	MovementComponent& operator=(const MovementComponent& other) = delete;
	MovementComponent& operator=(MovementComponent&& other) = delete;

	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void Move(float deltaTime, glm::vec3 direction);

	void SetDirection(glm::vec3 direction) { m_Direction = direction; }
	glm::vec3 GetDirection() { return m_Direction; }

	void SetHitWall(bool hit) { m_HitWall = hit; StopMoving(); }

	void StunForSeconds(float seconds);

private:
	void StopMoving();
	glm::vec3 m_Direction;
	float m_Speed;

	bool m_HitWall;

	bool m_Moving;
	float m_TraveledElementLength = 0;

	bool m_Stunned;
	std::chrono::time_point<std::chrono::steady_clock> m_StunStartTime;
	float m_StunDuration;

	glm::vec3 m_StartPos;
};

