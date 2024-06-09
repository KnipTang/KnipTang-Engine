#pragma once
#include <memory>
#include "Component.h"
#include "HealthComponent.h"
#include "PengoState.h"

class PengoComponent : public dae::Component
{
public:
	PengoComponent(dae::GameObject* gameObject) : dae::Component(gameObject) { m_State = std::make_unique<Idle>(); }
	~PengoComponent() override = default;

	PengoComponent(const PengoComponent& other) = delete;
	PengoComponent(PengoComponent&& other) = delete;
	PengoComponent& operator=(const PengoComponent& other) = delete;
	PengoComponent& operator=(PengoComponent&& other) = delete;

	void Update(float deltaTime) override;

	void HandleInput(Controlls control);

	void SetState(std::unique_ptr<PengoState> state) 
	{ 
		m_State = std::move(state); 
	}

	void SetCurrentDirection(glm::vec3 direction) { m_CurrentDirection = direction; }
	glm::vec3 GetCurrentDirection() { return m_CurrentDirection; }

	void SetPengoIsKilled(bool value) 
	{ 
		m_IsDead = value;

		if(m_IsDead)
			SetState(std::make_unique<DyingState>(GetOwner()));
		else
			SetState(std::make_unique<Idle>(GetOwner()));
	}
	bool IsPengoKilled() { return m_IsDead; }

private:
	std::unique_ptr<PengoState> m_State;

	glm::vec3 m_CurrentDirection;

	bool m_IsDead;
};

