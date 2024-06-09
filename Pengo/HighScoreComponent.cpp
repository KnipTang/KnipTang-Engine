#include "HighScoreComponent.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include "GameObject.h"

HighScoreComponent::HighScoreComponent(dae::GameObject* gameObject, const std::string filePath, dae::TextObject* textObject) : Component(gameObject), m_FilePath(filePath), m_DisplayComponent(textObject)
{
	m_HighScoreList = ReadHighScore();
	int highScore = GetHighestHighScore(m_HighScoreList);
	SetHighScore(highScore);
}

void HighScoreComponent::SetHighScore(int highScore)
{
	m_HighScore = highScore;

	UpdateDisplay();
}

std::vector<int> HighScoreComponent::ReadHighScore()
{
	std::vector<int> highScoreList;

	std::ifstream file(m_FilePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open high score file: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to open high score file");
	}

	int highScore;
	while (file >> highScore)
	{
		highScoreList.emplace_back(highScore);
	}

	std::sort(highScoreList.begin(), highScoreList.end(), std::greater<int>());

	return highScoreList;
}

void HighScoreComponent::WriteHighScore()
{
	if(!m_NewHighScore)
		return;

	std::ofstream file(m_FilePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open high score file for writing: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to open high score file for writing");
	}

	for (int score : m_HighScoreList)
	{
		file << score << std::endl;
	}

	if (file.fail())
	{
		std::cerr << "Failed to write high score to file: " << m_FilePath << std::endl;
		throw std::runtime_error("Failed to write high score to file");
	}
}

int HighScoreComponent::GetHighestHighScore(std::vector<int> highScoreList)
{
	if (highScoreList.empty())
	{
		return 0;
	}
	return highScoreList.front();
}

void HighScoreComponent::UpdateDisplay()
{
	if (m_DisplayComponent != nullptr)
		m_DisplayComponent->SetText(std::to_string(m_HighScore));
}

void HighScoreComponent::UpdateDisplayList()
{

	dae::GameObject* displayOwner = m_DisplayComponent->GetOwner();
	
	if (displayOwner->GetChildCount() <= 0)
		return;
	
	int childrenCount = static_cast<int>(displayOwner->GetChildCount());
	
	for (int i = 0; i < childrenCount; i++)
	{
		dae::TextObject* childDisplayComp = displayOwner->GetChildAt(i)->GetComponent<dae::TextObject>();
	
		if (childDisplayComp == nullptr)
			continue;

		childDisplayComp->SetText(std::to_string(m_HighScoreList.at(i)));
	}
}

void HighScoreComponent::NewHighScore(int highScore)
{
	m_NewHighScore = true;

	m_HighScoreList.pop_back();
	m_HighScoreList.emplace_back(highScore);

	std::sort(m_HighScoreList.begin(), m_HighScoreList.end(), std::greater<int>());
}
