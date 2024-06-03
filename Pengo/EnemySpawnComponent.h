#pragma once
#include <Component.h>
#include "Animation.h"
class EnemySpawnComponent : public dae::Component
{
public:
	EnemySpawnComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
	{
		m_EnemyAni = GetOwner()->GetComponent<Animation>();
		//if (m_EnemyAni != nullptr)
		//{
		//	//m_AnimationTime = m_EnemyAni->GetFlipTime() * m_EnemyAni->GetMaxFrames();
		//}
	}

	virtual ~EnemySpawnComponent() { }

	void Update(float deltaTime) override;

	void SpawnEnemy();

	EnemySpawnComponent(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent(EnemySpawnComponent&& other) = delete;
	EnemySpawnComponent& operator=(const EnemySpawnComponent& other) = delete;
	EnemySpawnComponent& operator=(EnemySpawnComponent&& other) = delete;

private:
	void ReplaceWallWithEnemy();

	//float m_CurrentTimer;
	//float m_AnimationTime;

	//bool m_AnimationDone = false;

	Animation* m_EnemyAni{};
};

