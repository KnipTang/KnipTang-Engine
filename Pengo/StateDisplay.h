#pragma once
#include "Observer.h"
#include "Component.h"
namespace dae
{
	class TextObject;
	class StateDisplay : public Observer, public Component
	{
	public:
		void Notify(GameEvent event, Subject* actor) override;

		void Update(float /*deltaTime*/) override { }
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		StateDisplay(GameObject* gameObject, std::string state, double startValue);
		virtual ~StateDisplay() { }
		StateDisplay(const StateDisplay& other) = delete;
		StateDisplay(StateDisplay&& other) = delete;
		StateDisplay& operator=(const StateDisplay& other) = delete;
		StateDisplay& operator=(StateDisplay&& other) = delete;
	private:
		std::string m_StateName;
		TextObject* m_TextObject;
	};
}

