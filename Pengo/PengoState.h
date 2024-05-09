#pragma once
#include <iostream>
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
	virtual PengoState* HandleInput(Controlls control) = 0;
	virtual PengoState* Update() = 0;
private: 
};

class MoveState : public PengoState
{
public:
	MoveState() {};
	MoveState* HandleInput(Controlls /*control*/) override
	{
		//if (Input.GetButtonUp(_duckAxisName)) {
		//	return new StandingState();
		//}
		return new MoveState;
	}
	MoveState* Update() override
	{ 
		/* do what you must do when ducking...*/
		std::cout << "Pushing\n"; 
		return nullptr;
	}

};

class PushingState : public PengoState
{
public:
	PushingState* HandleInput(Controlls /*control*/) override
	{
		//if (Input.GetButtonUp(_duckAxisName)) {
		//	return new StandingState();
		//}
		return nullptr;
	}
	PushingState* Update() override
	{ 
		/* do what you must do when ducking...*/  
		std::cout << "Pushing\n"; 
		return nullptr;
	}

};
