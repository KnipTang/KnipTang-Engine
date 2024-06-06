#pragma once

#include "Component.h"
#include "Subject.h"
#include "TextObject.h"
enum class PengoEvents {
	PlayerHit,
	PlayerDied,
	PointsChanged,
};

class StateDisplay : public dae::Component
{
public:
	void Notify(PengoEvents event, dae::Component* actor);

	void Update(float /*deltaTime*/) override { }
	void LateUpdate(float /*deltaTime*/) override {}
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	StateDisplay(dae::GameObject* gameObject, std::string state, double startValue);
	virtual ~StateDisplay() { }
	StateDisplay(const StateDisplay& other) = delete;
	StateDisplay(StateDisplay&& other) = delete;
	StateDisplay& operator=(const StateDisplay& other) = delete;
	StateDisplay& operator=(StateDisplay&& other) = delete;
private:
	std::string m_StateName;
	dae::TextObject* m_TextObject;
};
