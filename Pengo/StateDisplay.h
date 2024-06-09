#pragma once
#include "Component.h"
#include "TextObject.h"

enum class PengoEvents {
	PlayerHit,
	PlayerDied,
	PointsChanged,
};

class StateDisplay : public dae::Component
{
public:
	StateDisplay(dae::GameObject* gameObject, std::string state, double startValue);
	~StateDisplay() override = default;

	StateDisplay(const StateDisplay& other) = delete;
	StateDisplay(StateDisplay&& other) = delete;
	StateDisplay& operator=(const StateDisplay& other) = delete;
	StateDisplay& operator=(StateDisplay&& other) = delete;

	void Notify(PengoEvents event, dae::Component* actor);
private:
	std::string m_StateName;
	dae::TextObject* m_TextObject;
};
