#pragma once
#include "GameObject.h"

class BaseState
{
public:
	BaseState() = default;
	virtual ~BaseState() = default;

	BaseState(const BaseState& other) = delete;
	BaseState(BaseState&& other) = delete;
	BaseState& operator=(const BaseState& other) = delete;
	BaseState& operator=(BaseState&& other) = delete;

	virtual void Enter(dae::GameObject*) {}
	virtual void HandleInput(dae::GameObject*) {}
	virtual void Update() {}
};