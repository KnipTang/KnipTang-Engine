#include "HighScoreComponent.h"
#include <fstream>
#include <iostream>

HighScoreComponent::HighScoreComponent(dae::GameObject* gameObject, const std::string filePath, dae::TextObject* textObject) : Component(gameObject), m_FilePath(filePath), m_DisplayComponent(textObject)
{
	SetHighScore(ReadHighScore());
}

void HighScoreComponent::SetHighScore(int highScore)
{
	m_HighScore = highScore;

	UpdateDisplay();
}

int HighScoreComponent::ReadHighScore()
{
	int highScore;

	std::ifstream file(m_FilePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open high score file: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to open high score file");
	}

	file >> highScore;
	if (file.fail())
	{
		std::cerr << "Failed to read high score from file: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to read high score from file");
	}

	return highScore;
}

void HighScoreComponent::WriteHighScore(int highScore) const
{
	std::ofstream file(m_FilePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open high score file for writing: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to open high score file for writing");
	}

	file << highScore;
	if (file.fail())
	{
		std::cerr << "Failed to write high score to file: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to write high score to file");
	}
}

void HighScoreComponent::UpdateDisplay()
{
	if (m_DisplayComponent != nullptr)
		m_DisplayComponent->SetText(std::to_string(m_HighScore));
}
