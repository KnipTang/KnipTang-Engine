#pragma once
#include <Component.h>
class TimerComponent : public dae::Component
{
public:
	void Update(float deltaTime) override;

	double GetCurrentGameTime() { return m_CurrentTime; }

	TimerComponent(dae::GameObject* gameObject) : dae::Component(gameObject) {}
	virtual ~TimerComponent() { }
	TimerComponent(const TimerComponent& other) = delete;
	TimerComponent(TimerComponent&& other) = delete;
	TimerComponent& operator=(const TimerComponent& other) = delete;
	TimerComponent& operator=(TimerComponent&& other) = delete;
private:
	double m_CurrentTime;
};

