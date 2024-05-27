#pragma once
#include <Component.h>
class WallComponent : public dae::Component
{
public:
	void DeleteWall();

	WallComponent(dae::GameObject* gameObject) : dae::Component(gameObject) {};
	virtual ~WallComponent() { }
	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) = delete;
};

