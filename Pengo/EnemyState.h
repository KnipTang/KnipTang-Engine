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

	virtual void Enter(dae::GameObject*) {};
	virtual void Update() {};
private:
};

class IdleState : public EnemyState
{
public:
	IdleState(dae::GameObject* gameObject)
	{
		m_AnimationComp = gameObject->GetComponent<Animation>();

		Enter(gameObject);
	}
	~IdleState() override = default;

	void Enter(dae::GameObject* gameObject) override;
private:
	Animation* m_AnimationComp;
};

class MovingState : public EnemyState
{
public:
	MovingState(dae::GameObject* gameObject, glm::vec3 direction) 
	{ 
		m_AnimationComp = gameObject->GetComponent<Animation>();

		m_CurrentState = ActionState::DOWN;

		if (direction == glm::vec3(0, -1, 0)) {
			m_CurrentState = ActionState::UP;
		}
		else if (direction == glm::vec3(0, 1, 0)) {
			m_CurrentState = ActionState::DOWN;
		}
		else if (direction == glm::vec3(-1, 0, 0)) {
			m_CurrentState = ActionState::LEFT;
		}
		else if (direction == glm::vec3(1, 0, 0)) {
			m_CurrentState = ActionState::RIGHT;
		}

		Enter(gameObject);
	}
	~MovingState() override = default;

	void Enter(dae::GameObject* gameObject) override;
private:
	Animation* m_AnimationComp;
	ActionState m_CurrentState;
};

class EnemyComponent;
class SpawningState : public EnemyState
{
public:
	SpawningState(dae::GameObject* gameObject)
	{
		m_AnimationComp = gameObject->GetComponent<Animation>();
		m_EnemyComp = gameObject->GetComponent<EnemyComponent>();
		Enter(gameObject);
	}
	~SpawningState() override = default;

	void Enter(dae::GameObject* gameObject) override;
	void Update() override;
private:
	Animation* m_AnimationComp;
	EnemyComponent* m_EnemyComp;
};