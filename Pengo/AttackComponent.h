#pragma once
#include <Component.h>
#include <iostream>
#include "GameObject.h"
class AttackComponent : public dae::Component
{
public:
	void Update(float) override {};
	void LateUpdate(float) override 
	{ 
		if (m_AttackReady) m_AttackReady = false;
		if (m_JoyStickPressed) m_JoyStickPressed = false;
	}
	void FixedUpdate(float) override {}
	void Render() const override {}

	void Attack();

	void JoyStickPressed() { m_JoyStickPressed = true; };

	void SetAttackReady(bool value) 
	{ 
		m_AttackReady = value; 
	}

	void SetInfrontObject(dae::GameObject* gameObject)
	{
		m_ObjectInfront = gameObject;
	}

	AttackComponent(dae::GameObject* gameObject) : dae::Component(gameObject) 
	{
		m_ObjectInfront = nullptr;
		m_AttackReady = false;
	};
	virtual ~AttackComponent() { }
	AttackComponent(const AttackComponent& other) = delete;
	AttackComponent(AttackComponent&& other) = delete;
	AttackComponent& operator=(const AttackComponent& other) = delete;
	AttackComponent& operator=(AttackComponent&& other) = delete;
private:
	dae::GameObject* m_ObjectInfront;

	bool m_AttackReady;

	bool m_JoyStickPressed;
};
