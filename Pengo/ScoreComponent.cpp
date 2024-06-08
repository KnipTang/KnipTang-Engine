#include "ScoreComponent.h"

void ScoreComponent::SetScore(int score)
{
	m_CurrentScore = score;
	UpdateDisplay();
	UpdateHighScore();
}

void ScoreComponent::AddScore(int score)
{
	m_CurrentScore += score;
	UpdateDisplay();
	UpdateHighScore();
}

void ScoreComponent::UpdateDisplay()
{
	if (m_DisplayComponent != nullptr)
		m_DisplayComponent->SetText(std::to_string(m_CurrentScore));
}

void ScoreComponent::UpdateHighScore()
{
	if (m_HighScoreComp == nullptr)
		return;

	if (m_CurrentScore > m_CurrentLowestHighScore)
	{
		m_CurrentLowestHighScore = m_CurrentScore;
		m_HighScoreComp->SetHighScore(m_CurrentLowestHighScore);
		m_HighScoreComp->NewHighScore(m_CurrentLowestHighScore);
	}
}
