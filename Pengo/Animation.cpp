#include "Animation.h"

void Animation::Update(float deltaTime)
{
	m_Time += deltaTime;

	if (m_Time >= m_FlipTime)
	{
		if (GetOwner()->HasComponent<dae::RenderComponent>())
		{
			dae::RenderComponent* renderComp = GetOwner()->GetComponent<dae::RenderComponent>();
			SDL_Rect currentSourceRect = m_CurrentSourceRect;

			if (m_CurrentFrame < m_MaxFrames)
			{
				currentSourceRect.x += 16;
				m_CurrentFrame++;
			}
			else
			{
				m_CurrentFrame = 0;
			}

			renderComp->SetSourceRect(currentSourceRect.x, currentSourceRect.y, currentSourceRect.w, currentSourceRect.h);
		}

		m_Time = 0;
	}
}
