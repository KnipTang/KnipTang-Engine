#pragma once
#include <Component.h>
#include "GameObject.h"
class WallMovementComponent : public dae::Component
{
public:
	WallMovementComponent(dae::GameObject* gameObject, float speed = 40.f) : dae::Component(gameObject), m_Speed(speed)
	{
		m_HitWall = false;
		m_Moving = false;
		m_Vibrate = false;
	}
	~WallMovementComponent() override = default;

	WallMovementComponent(const WallMovementComponent& other) = delete;
	WallMovementComponent(WallMovementComponent&& other) = delete;
	WallMovementComponent& operator=(const WallMovementComponent& other) = delete;
	WallMovementComponent& operator=(WallMovementComponent&& other) = delete;

	void Update(float deltaTime) override;
	void LateUpdate(float) override;

	void Move(glm::vec3 direction, dae::GameObject* moverOwner);

	bool IsWallMoving() { return m_Moving; }

	void SetDirection(glm::vec3 direction) { m_Direction = direction; }
	glm::vec3 GetDirection() { return m_Direction; }

	void SetHitWall(bool hit);

	void RoundOffWallPos();

	void Vibrate();
	bool IsVibrating() { return m_Vibrate; }

private:
	glm::vec3 m_Direction;
	float m_Speed;

	bool m_HitWall;
	bool m_Moving;

	float m_TraveledElementLength = 0;
	float m_TraveledTotalLength = 0;
	glm::vec3 m_StartPos;

	dae::GameObject* m_MoverOwner;

	bool m_Vibrate;
	float m_CurrentVibrationTime = 0;
	float m_MaxVibrationTime = 1.f;
};
