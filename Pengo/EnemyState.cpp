#include <iostream>
#include "EnemyState.h"

void MovingState::Enter(dae::GameObject*, ActionState actionState)
{
	if (m_AnimationComp != nullptr)
	{
		m_AnimationComp->ToggleAnimation(true);
		m_AnimationComp->ToggleLooping(true);
		m_AnimationComp->SetMaxFrames(1);

		SDL_Rect currentStartingRect = m_AnimationComp->GetCurrentSourceRect();

		switch (actionState)
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
