#include "Animation.h"
#include "InputManager.h"

Animation::Animation(dae::GameObject* gameObject, bool animationOn, int maxFrames, bool loopAnimation, bool resetWhenDone, float flipTime) : dae::Component(gameObject)
{
	m_AnimationOn = animationOn;
	m_MaxFrames = maxFrames;
	m_LoopAnimation = loopAnimation;
	m_ResetWhenDone = resetWhenDone;

	m_FlipTime = flipTime;

	m_RenderComp = GetOwner()->GetComponent<dae::RenderComponent>();
	m_StartSourceRect = m_RenderComp->GetSourceRect();
	m_CurrentSourceRect = m_StartSourceRect;
}

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

void Animation::SetStartSourceRect(SDL_Rect startSourceRect)
{
	m_StartSourceRect = startSourceRect;
	SetCurrentSourceRect(m_StartSourceRect);
}

void Animation::SetCurrentSourceRect(SDL_Rect currentSourceRect)
{
	m_CurrentSourceRect = currentSourceRect;
	if (m_RenderComp != nullptr)
	{
		m_RenderComp->SetSourceRect(m_CurrentSourceRect.x, m_CurrentSourceRect.y, m_CurrentSourceRect.w, m_CurrentSourceRect.h);
	}
}
