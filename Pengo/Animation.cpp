#include "Animation.h"
#include <iostream>
#include "InputManager.h"

void Animation::Update(float deltaTime)
{
	if (!m_AnimationOn)
		return;

	m_CurrentTime += deltaTime;
	
	if (m_CurrentTime >= m_FlipTime)
	{
		if (GetOwner()->HasComponent<dae::RenderComponent>())
		{
			if (m_CurrentFrame < m_MaxFrames)
			{
				m_CurrentSourceRect.x += 16;
				m_CurrentFrame++;
			}
			else
			{
				if (!m_LoopAnimation)
				{
					m_AnimationOn = false;
					if(m_ResetWhenDone)
						SetCurrentSourceRect(m_StartSourceRect);
					return;
				}
				m_CurrentFrame = 0;
				m_CurrentSourceRect = m_StartSourceRect;
			}

			m_RenderComp->SetSourceRect(m_CurrentSourceRect.x, m_CurrentSourceRect.y, m_CurrentSourceRect.w, m_CurrentSourceRect.h);
		}

		m_CurrentTime = 0;
	}
}

void Animation::ToggleLooping(bool loopValue)
{
	m_LoopAnimation = loopValue;
}

void Animation::ToggleResetWhenDone(bool resetWhenDone)
{
	m_ResetWhenDone = resetWhenDone;
}
