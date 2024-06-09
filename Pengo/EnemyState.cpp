#include "EnemyState.h"
#include "EnemyComponent.h"
#include "GameObject.h"

void IdleState::Enter(dae::GameObject*)
{
	if (m_AnimationComp != nullptr)
	{
		m_AnimationComp->ToggleAnimation(false);
		m_AnimationComp->ToggleLooping(false);
		m_AnimationComp->SetMaxFrames(1);

		SDL_Rect currentStartingRect = { 16 * 0, 16 * 9, 16, 16 };

		m_AnimationComp->SetStartSourceRect(currentStartingRect);
	}
}

void MovingState::Enter(dae::GameObject*)
{
	if (m_AnimationComp != nullptr)
	{
		m_AnimationComp->ToggleAnimation(true);
		m_AnimationComp->ToggleLooping(true);
		m_AnimationComp->SetMaxFrames(1);

		SDL_Rect currentStartingRect = m_AnimationComp->GetCurrentSourceRect();

		switch (m_CurrentState)
		{
		case ActionState::UP:
			currentStartingRect = { 16 * 4, 16 * 9, 16, 16 };
			break;
		case ActionState::DOWN:
			currentStartingRect = { 16 * 0, 16 * 9, 16, 16 };
			break;
		case ActionState::LEFT:
			currentStartingRect = { 16 * 2, 16 * 9, 16, 16 };
			break;
		case ActionState::RIGHT:
			currentStartingRect = { 16 * 6, 16 * 9, 16, 16 };
			break;
		}

		m_AnimationComp->SetStartSourceRect(currentStartingRect);
	}
}

void SpawningState::Enter(dae::GameObject*)
{
	if (m_AnimationComp != nullptr)
	{
		m_AnimationComp->ToggleAnimation(true);
		m_AnimationComp->ToggleLooping(false);
		m_AnimationComp->SetMaxFrames(5);
		m_AnimationComp->SetFlipTime(0.25f);

		SDL_Rect currentStartingRect = { 0, 16 * 8, 16, 16 };

		m_AnimationComp->SetStartSourceRect(currentStartingRect);
	}
}

void SpawningState::Update()
{
	if (!m_AnimationComp->IsAnimating())
	{
		if (m_EnemyComp != nullptr)
		{
			m_EnemyComp->SetState(std::make_unique<IdleState>(m_EnemyComp->GetOwner()));
		}
	}
}

