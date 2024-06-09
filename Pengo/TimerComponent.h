#pragma once
#include <Component.h>
class TimerComponent : public dae::Component
{
public:
	TimerComponent(dae::GameObject* gameObject) : dae::Component(gameObject) {}
	~TimerComponent() override = default;

	TimerComponent(const TimerComponent& other) = delete;
	TimerComponent(TimerComponent&& other) = delete;
	TimerComponent& operator=(const TimerComponent& other) = delete;
	TimerComponent& operator=(TimerComponent&& other) = delete;

	void Update(float deltaTime) override;

	double GetCurrentGameTime() { return m_CurrentTime; }

private:
	double m_CurrentTime;
};

