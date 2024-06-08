#pragma once
#include "GameObject.h"

class BaseState
{
public:
	BaseState() = default;
	virtual ~BaseState() = default;

	virtual void Enter(dae::GameObject*) {}
	virtual void HandleInput(dae::GameObject*) {}
	virtual void Update() {}
private:
};