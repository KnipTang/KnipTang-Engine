#pragma once
#include "Component.h"
#include "Subject.h"
namespace dae
{
    class ScoreComponent : public Component, public Subject
    {
	public:
		void Update(float /*deltaTime*/) override { }
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		int GetPoints() { return m_CurrentPoints; }
		void SetPoints(int points);

		void AddPoints(int points);

		ScoreComponent(GameObject* gameObject) : Component(gameObject), Subject(gameObject) {}
		virtual ~ScoreComponent() { }
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

	private:
		int m_CurrentPoints = 0;
    };
}

