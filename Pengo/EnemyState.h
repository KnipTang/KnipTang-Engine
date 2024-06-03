#pragma once
#include "GameObject.h"
#include "Animation.h"
enum class ActionState
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ATTACK
};

class EnemyState
{
public:
	EnemyState() = default;
	virtual ~EnemyState() = default;

	virtual void Enter(dae::GameObject* gameObject, ActionState actionState) = 0;
private:
};

class MovingState : public EnemyState
{
public:
	MovingState(dae::GameObject* gameObject, glm::vec3 direction) 
	{ 
		m_AnimationComp = gameObject->GetComponent<Animation>();

		ActionState currentState = ActionState::DOWN;

		if (direction == glm::vec3(0, -1, 0)) {
			currentState = ActionState::UP;
		}
		else if (direction == glm::vec3(0, 1, 0)) {
			currentState = ActionState::DOWN;
		}
		else if (direction == glm::vec3(-1, 0, 0)) {
			currentState = ActionState::LEFT;
		}
		else if (direction == glm::vec3(1, 0, 0)) {
			currentState = ActionState::RIGHT;
		}

		Enter(gameObject, currentState);
	}
	~MovingState() override = default;

	void Enter(dae::GameObject* gameObject, ActionState actionState) override;

private:
	Animation* m_AnimationComp;
};