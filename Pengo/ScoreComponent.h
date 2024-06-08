#pragma once
#include "Component.h"
#include "Subject.h"
#include "TextObject.h"

class ScoreComponent : public dae::Component
{
public:
	void Update(float /*deltaTime*/) override { }
	void LateUpdate(float /*deltaTime*/) override {}
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	int GetScore() { return m_CurrentScore; }
	void SetScore(int score);

	void AddScore(int score);

	ScoreComponent(dae::GameObject* gameObject, dae::TextObject* textObject = nullptr) : Component(gameObject), m_DisplayComponent(textObject) {}
	virtual ~ScoreComponent() { }
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

private:
	void UpdateDisplay();

	int m_CurrentScore = 0;
	dae::TextObject* m_DisplayComponent;
};

