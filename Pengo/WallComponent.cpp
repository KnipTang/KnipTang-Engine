#include "WallComponent.h"
#include "GameObject.h"
#include "Animation.h"

WallComponent::WallComponent(dae::GameObject* gameObject) : dae::Component(gameObject)
{
}

void WallComponent::Update(float deltaTime)
{
	if (m_Delete)
	{
		m_WallCurrentDeleteTime += deltaTime;

		if (m_WallCurrentDeleteTime >= m_WallDeleteTime)
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
	Animation* animationComp = GetOwner()->GetComponent<Animation>();
	if (animationComp != nullptr)
	{
		SDL_Rect deletingWallStartingRect = { 708, 48, 16, 16 };

		animationComp->ToggleAnimation(true);
		animationComp->SetStartSourceRect(deletingWallStartingRect);

		m_WallDeleteTime = animationComp->GetMaxFrames() * animationComp->GetFlipTime();
	}
}
