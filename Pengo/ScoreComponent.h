#pragma once
#include "Component.h"
#include "HighScoreComponent.h"
#include "TextObject.h"

class ScoreComponent : public dae::Component
{
public:
	ScoreComponent(dae::GameObject* gameObject, HighScoreComponent* highScoreComp = nullptr, dae::TextObject* textObject = nullptr) : Component(gameObject), m_HighScoreComp(highScoreComp), m_DisplayComponent(textObject)
	{
		if(highScoreComp != nullptr)
			m_CurrentLowestHighScore = m_HighScoreComp->GetLowestHighScore();
	}
	~ScoreComponent() override = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	int GetScore() { return m_CurrentScore; }
	void SetScore(int score);

	void AddScore(int score);

	void SetDisplayComponent(dae::TextObject* displayComp) { m_DisplayComponent = displayComp; UpdateDisplay();}

private:
	void UpdateDisplay();
	void UpdateHighScore();

	int m_CurrentScore = 0;
	int m_CurrentLowestHighScore;

	dae::TextObject* m_DisplayComponent;
	HighScoreComponent* m_HighScoreComp;
};
