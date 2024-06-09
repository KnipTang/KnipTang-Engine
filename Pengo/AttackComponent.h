#pragma once
#include <Component.h>
#include "GameObject.h"

class AttackComponent : public dae::Component
{
public:
	AttackComponent(dae::GameObject* gameObject) : dae::Component(gameObject) 
	{
		m_ObjectInfront = nullptr;
		m_AttackReady = false;
		m_JoyStickPressed = false;
	}
	~AttackComponent() override = default;
	AttackComponent(const AttackComponent& other) = delete;
	AttackComponent(AttackComponent&& other) = delete;
	AttackComponent& operator=(const AttackComponent& other) = delete;
	AttackComponent& operator=(AttackComponent&& other) = delete;

	void LateUpdate(float) override 
	{ 
		if (m_AttackReady) m_AttackReady = false;
		if (m_JoyStickPressed) m_JoyStickPressed = false;
	}

	void Attack();

	void JoyStickPressed();

	void SetAttackReady(bool value) 
	{ 
		m_AttackReady = value; 
	}

	void SetInfrontObject(dae::GameObject* gameObject)
	{
		m_ObjectInfront = gameObject;
	}

private:
	dae::GameObject* m_ObjectInfront;

	bool m_AttackReady;

	bool m_JoyStickPressed;
};
