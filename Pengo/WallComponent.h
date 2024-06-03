#pragma once
#include <Component.h>
class WallComponent : public dae::Component
{
public:
	WallComponent(dae::GameObject* gameObject);
	virtual ~WallComponent() { }

	void Update(float deltaTime) override;

	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) = delete;

	void DeleteWall();
	void PlayBreakWall();
	float GetTimeToBreakWall() { return m_WallDeleteTime; }

	bool IsWallDeleting() { return m_Delete; }
private:
	bool m_Delete = false;

	float m_WallCurrentDeleteTime = 0;
	float m_WallDeleteTime;
};

