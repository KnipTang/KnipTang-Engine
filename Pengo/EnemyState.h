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

	EnemyState(const EnemyState& other) = delete;
	EnemyState(EnemyState&& other) = delete;
	EnemyState& operator=(const EnemyState& other) = delete;
	EnemyState& operator=(EnemyState&& other) = delete;

	virtual void Enter(dae::GameObject*) {}
	virtual void Update() {}
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

	IdleState(const IdleState& other) = delete;
	IdleState(IdleState&& other) = delete;
	IdleState& operator=(const IdleState& other) = delete;
	IdleState& operator=(IdleState&& other) = delete;

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

	MovingState(const MovingState& other) = delete;
	MovingState(MovingState&& other) = delete;
	MovingState& operator=(const MovingState& other) = delete;
	MovingState& operator=(MovingState&& other) = delete;

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

	SpawningState(const SpawningState& other) = delete;
	SpawningState(SpawningState&& other) = delete;
	SpawningState& operator=(const SpawningState& other) = delete;
	SpawningState& operator=(SpawningState&& other) = delete;

	void Enter(dae::GameObject* gameObject) override;
	void Update() override;
private:
	Animation* m_AnimationComp;
	EnemyComponent* m_EnemyComp;
};