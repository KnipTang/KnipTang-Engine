#include "EndScreenComponent.h"

#include "ScoreComponent.h"
#include "TextObject.h"
#include "TimerComponent.h"

void EndScreenComponent::Update(float)
{
	if (m_IsDateDirty)
	{
		SetupEndScreen();
		m_IsDateDirty = false;
	}
}

EndScreenComponent::EndScreenComponent(dae::GameObject* gameObject) : Component(gameObject)
{

}

void EndScreenComponent::SetupEndScreen()
{
	m_EndScene = dae::SceneManager::GetInstance().GetSceneByName("EndScene");
	m_GameStatsScene = dae::SceneManager::GetInstance().GetSceneByName("GameStats");

	dae::GameObject* scoreObj = m_EndScene->GetGameObjectWithLayer("Score");
	dae::TextObject* textScoreObject = scoreObj->GetComponent<dae::TextObject>();
	ScoreComponent* scoreComp = m_GameStatsScene->GetGameObjectWithLayer("Score")->GetComponent<ScoreComponent>();

	scoreComp->SetDisplayComponent(textScoreObject);

	scoreComp->AddScore(CalculateBonusScore());
}

int EndScreenComponent::CalculateBonusScore()
{
	TimerComponent* timerComp = m_GameStatsScene->GetGameObjectWithLayer("Timer")->GetComponent<TimerComponent>();
	int currentTime = static_cast<int>(timerComp->GetCurrentTime());

	if(currentTime <= m_MaxBonusTime)
	{
		int bonusTime = m_MaxBonusTime - currentTime;

		int bonusScore = m_BonusScorePerSec * bonusTime;
		return bonusScore;
	}

	return 0;
}
