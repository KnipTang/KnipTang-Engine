#pragma once
#include "Component.h"
#include "Scene.h"

class EndScreenComponent : public dae::Component
{
public:
	EndScreenComponent(dae::GameObject* gameObject);
	~EndScreenComponent() override = default;

	EndScreenComponent(const EndScreenComponent& other) = delete;
	EndScreenComponent(EndScreenComponent&& other) = delete;
	EndScreenComponent& operator=(const EndScreenComponent& other) = delete;
	EndScreenComponent& operator=(EndScreenComponent&& other) = delete;

	void Update(float) override;

	void SetupEndScreen();

private:
	int CalculateBonusScore();

	dae::Scene* m_EndScene;
	dae::Scene* m_GameStatsScene;

	int m_MaxBonusTime = 60;
	int m_BonusScorePerSec = 50;

	bool m_IsDateDirty = true;
};

