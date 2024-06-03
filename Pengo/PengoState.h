#pragma once
#include <iostream>
#include "Animation.h"
#include "MovementComponent.h"

class MoveState;
class DyingState;
class PushingState;

enum class Controlls
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ATTACK
};

class PengoState
{
public: 
	PengoState() {};
	virtual ~PengoState() {}

	virtual void Enter(dae::GameObject* gameObject) = 0;
	virtual std::unique_ptr<PengoState> HandleInput(dae::GameObject* gameObject, Controlls control) = 0;
	virtual std::unique_ptr<PengoState> Update() = 0;
private: 
};

class DyingState : public PengoState
{
public:
	DyingState() {};
	DyingState(dae::GameObject* gameObject) { Enter(gameObject); }
	~DyingState() override {};

	void Enter(dae::GameObject* gameObject) override;

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* /*gameObject*/, Controlls /*control*/) override;
	std::unique_ptr<PengoState> Update() override;
};

class PushingState : public PengoState
{
public:
	PushingState() {};
	~PushingState() override {};

	void Enter(dae::GameObject* /*gameObject*/) override {};

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* /*gameObject*/, Controlls /*control*/) override
	{
		return nullptr;
	}
	std::unique_ptr<PengoState> Update() override
	{ 
		return nullptr;
	}

};

class MoveState : public PengoState
{
public:
	MoveState() {};
	MoveState(dae::GameObject* gameObject) { Enter(gameObject); }
	MoveState(dae::GameObject* gameObject, Controlls control) { Enter(gameObject, control); }
	~MoveState() override {};

	void Enter(dae::GameObject* gameObject) override;
	void Enter(dae::GameObject* gameObject, Controlls control);

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* gameObject, Controlls control) override;
	std::unique_ptr<PengoState> Update() override
	{
		return std::make_unique<MoveState>();
	}
};

class Idle : public PengoState
{
public:
	Idle() {};
	Idle(dae::GameObject* gameObject) { Enter(gameObject); }
	~Idle() override {};

	void Enter(dae::GameObject* gameObject) override;

	std::unique_ptr<PengoState> HandleInput(dae::GameObject*, Controlls control) override;

	std::unique_ptr<PengoState> Update() override
	{
		return std::make_unique<PushingState>();
	}

};