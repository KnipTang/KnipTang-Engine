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

	void Enter(dae::GameObject* gameObject) override
	{
		SDL_Rect currentRect{};

		Animation* animationComp = gameObject->GetComponent<Animation>();
		if (animationComp != nullptr)
		{
			currentRect = animationComp->GetCurrentSourceRect();

			currentRect.x = 0;
			currentRect.y = 16 * 2;

			animationComp->SetCurrentSourceRect(currentRect);
		}

		gameObject->RemoveComponent(gameObject->GetComponent<MovementComponent>());
	}

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* /*gameObject*/, Controlls /*control*/) override
	{
		return std::make_unique<DyingState>();
	}
	std::unique_ptr<PengoState> Update() override
	{
		std::cout << "Dying :OO\n";
		return std::make_unique<DyingState>();
	}
};

class PushingState : public PengoState
{
public:
	PushingState() {};
	~PushingState() override {};

	void Enter(dae::GameObject* /*gameObject*/) override
	{

	}

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
	MoveState() { };
	~MoveState() override {};

	void Enter(dae::GameObject* /*gameObject*/) override
	{
		//std::cout << "ENtered";
	}

	std::unique_ptr<PengoState> HandleInput(dae::GameObject* gameObject, Controlls control) override
	{
		SDL_Rect currentRect{};

		Animation* animationComp = gameObject->GetComponent<Animation>();
		if (animationComp != nullptr)
			currentRect = animationComp->GetCurrentSourceRect();

		switch (control)
		{
		case Controlls::UP:
			if (animationComp != nullptr)
				currentRect.x = 16 * 4;
			break;

		case Controlls::DOWN:
			if (animationComp != nullptr)
				currentRect.x = 16 * 0;
			break;

		case Controlls::LEFT:
			if (animationComp != nullptr)
				currentRect.x = 16 * 2;
			break;

		case Controlls::RIGHT:
			if (animationComp != nullptr)
				currentRect.x = 16 * 6;
			break;

		case Controlls::ATTACK:
			return std::make_unique<PushingState>();
			break;
		}

		if (animationComp != nullptr)
			animationComp->SetCurrentSourceRect(currentRect);

		return std::make_unique<MoveState>();
	}

	std::unique_ptr<PengoState> Update() override
	{
		return std::make_unique<MoveState>();
	}

};