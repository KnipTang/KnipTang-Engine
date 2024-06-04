#include "WallComponent.h"
#include "GameObject.h"
#include "Animation.h"

WallComponent::WallComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{
}

void WallComponent::Update(float)
{
	if (m_Delete)
	{
		if (!m_AnimationComp->IsAnimating())
		{
			GetOwner()->RemoveGameObject();
		}
	}
}

void WallComponent::DeleteWall()
{
	if (m_Delete)
		return;

	m_Delete = true;

	PlayBreakWall();
}

void WallComponent::PlayBreakWall()
{
	m_AnimationComp = GetOwner()->GetComponent<Animation>();
	if (m_AnimationComp != nullptr)
	{
		SDL_Rect deletingWallStartingRect = { 708, 48, 16, 16 };

		m_AnimationComp->ToggleAnimation(true);
		m_AnimationComp->SetStartSourceRect(deletingWallStartingRect);
		m_AnimationComp->SetMaxFrames(8);
		m_AnimationComp->SetFlipTime(0.1f);
	}
}
