#pragma once
#include <Component.h>
class Animation;
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

	bool IsWallDeleting() { return m_Delete; }
private:
	bool m_Delete = false;
	Animation* m_AnimationComp;
};

