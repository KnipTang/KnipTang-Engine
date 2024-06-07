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

	virtual void Enter(dae::GameObject*) {};
	virtual std::unique_ptr<PengoState> HandleInput(dae::GameObject*, Controlls) { return std::make_unique<PengoState>(); };
	virtual std::unique_ptr<PengoState> Update(float) { return std::make_unique<PengoState>(); };
private: 
};

class PengoComponent;
class Animation;
class DyingState : public PengoState
{
public:
	DyingState() {};
	DyingState(dae::GameObject* gameObject) { Enter(gameObject); }
	~DyingState() override {};

	void Enter(dae::GameObject* gameObject) override;

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* /*gameObject*/, Controlls /*control*/) override;
	std::unique_ptr<PengoState> Update(float deltaTime) override;

private:
	float m_MaxRespawnTime = 3;
	float m_CurrentRespawnTime;
	bool  m_Respawning;

	Animation* m_AniComp;
	PengoComponent* m_PengoComp;
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
	std::unique_ptr<PengoState> Update(float) override
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
	std::unique_ptr<PengoState> Update(float) override
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

	std::unique_ptr<PengoState> Update(float) override
	{
		return std::make_unique<PushingState>();
	}

};