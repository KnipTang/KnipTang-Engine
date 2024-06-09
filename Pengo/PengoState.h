#pragma once
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
	PengoState() = default;
	virtual ~PengoState() = default;

	PengoState(const PengoState& other) = delete;
	PengoState(PengoState&& other) = delete;
	PengoState& operator=(const PengoState& other) = delete;
	PengoState& operator=(PengoState&& other) = delete;

	virtual void Enter(dae::GameObject*) {};
	virtual std::unique_ptr<PengoState> HandleInput(dae::GameObject*, Controlls) { return std::make_unique<PengoState>(); };
	virtual std::unique_ptr<PengoState> Update(float) { return std::make_unique<PengoState>(); };
};

class PengoComponent;
class Animation;
class DyingState : public PengoState
{
public:
	DyingState() = default;
	DyingState(dae::GameObject* gameObject) { Enter(gameObject); }
	~DyingState() override = default;

	DyingState(const DyingState& other) = delete;
	DyingState(DyingState&& other) = delete;
	DyingState& operator=(const DyingState& other) = delete;
	DyingState& operator=(DyingState&& other) = delete;

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
	PushingState() = default;
	~PushingState() override = default;

	PushingState(const PushingState& other) = delete;
	PushingState(PushingState&& other) = delete;
	PushingState& operator=(const PushingState& other) = delete;
	PushingState& operator=(PushingState&& other) = delete;

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
	~MoveState() override = default;

	MoveState(const MoveState& other) = delete;
	MoveState(MoveState&& other) = delete;
	MoveState& operator=(const MoveState& other) = delete;
	MoveState& operator=(MoveState&& other) = delete;

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
	~Idle() override = default;
	Idle(const Idle& other) = delete;
	Idle(Idle&& other) = delete;
	Idle& operator=(const Idle& other) = delete;
	Idle& operator=(Idle&& other) = delete;

	void Enter(dae::GameObject* gameObject) override;

	std::unique_ptr<PengoState> HandleInput(dae::GameObject*, Controlls control) override;

	std::unique_ptr<PengoState> Update(float) override
	{
		return std::make_unique<PushingState>();
	}
};