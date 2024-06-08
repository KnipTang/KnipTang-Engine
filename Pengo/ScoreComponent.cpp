#include "ScoreComponent.h"

void ScoreComponent::SetScore(int score)
{
	m_CurrentScore = score;
	UpdateDisplay();
}

void ScoreComponent::AddScore(int score)
{
	m_CurrentScore += score;
	UpdateDisplay();
}

void ScoreComponent::UpdateDisplay()
{
	if (m_DisplayComponent != nullptr)
		m_DisplayComponent->SetText(std::to_string(m_CurrentScore));
}
