#pragma once
#include <Component.h>
#include <string>
#include <vector>

#include "TextObject.h"

class HighScoreComponent : public dae::Component
{
public:
	void Update(float /*deltaTime*/) override { }
	void LateUpdate(float /*deltaTime*/) override {}
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {}

	int GetHighScore() { return m_HighScore; }
	void SetHighScore(int highScore);

	int GetLowestHighScore() { return m_HighScoreList.back(); }

	void SetDisplayComponent(dae::TextObject* displayComp) { m_DisplayComponent = displayComp; UpdateDisplay(); }
	dae::TextObject* GetDisplayComponent()
	{
		if(m_DisplayComponent != nullptr)
			return m_DisplayComponent;
		return nullptr;
	}

	void NewHighScore(int highScore);

	void UpdateDisplayList();

	HighScoreComponent(dae::GameObject* gameObject, const std::string filePath, dae::TextObject* textObject = nullptr);
	virtual ~HighScoreComponent() { WriteHighScore(); }
	HighScoreComponent(const HighScoreComponent& other) = delete;
	HighScoreComponent(HighScoreComponent&& other) = delete;
	HighScoreComponent& operator=(const HighScoreComponent& other) = delete;
	HighScoreComponent& operator=(HighScoreComponent&& other) = delete;

private:
	std::vector<int> ReadHighScore();
	void WriteHighScore();

	int GetHighestHighScore(std::vector<int> highScoreList);

	void UpdateDisplay();


	std::string m_FilePath;

	int m_HighScore;
	std::vector<int> m_HighScoreList;

	bool m_NewHighScore;

	dae::TextObject* m_DisplayComponent;
};

