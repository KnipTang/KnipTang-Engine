#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include <vector>
class Animation : public dae::Component
{
public:
	void Update(float deltaTime) override;
	void LateUpdate(float /*deltaTime*/) override {}
	void FixedUpdate(float /*fixedTimeStep*/) override {}
	void Render() const override {};

	void SetStartSourceRect(SDL_Rect startSourceRect)
	{
		m_StartSourceRect = startSourceRect;
		SetCurrentSourceRect(m_StartSourceRect);
	}
	SDL_Rect GetStartSourceRect()
	{
		return m_StartSourceRect;
	}

	void SetCurrentSourceRect(SDL_Rect currentSourceRect) 
	{ 
		m_CurrentSourceRect = currentSourceRect; 
		if (m_RenderComp != nullptr)
		{
			m_RenderComp->SetSourceRect(m_CurrentSourceRect.x, m_CurrentSourceRect.y, m_CurrentSourceRect.w, m_CurrentSourceRect.h);
		}
	}
	SDL_Rect GetCurrentSourceRect() { return m_CurrentSourceRect; }

	void ToggleAnimation(bool animation) { m_AnimationOn = animation; };
	bool IsAnimating() { return m_AnimationOn; }

	float GetFlipTime() { return m_FlipTime; }
	int GetMaxFrames() { return m_MaxFrames; }

	Animation(dae::GameObject* gameObject, bool animationOn = false, int maxFrames = 1, bool loopAnimation = false) : dae::Component(gameObject)
	{ 
		m_AnimationOn = animationOn;
		m_MaxFrames = maxFrames;
		m_LoopAnimation = loopAnimation;

		m_FlipTime = 0.25f;

		m_RenderComp = GetOwner()->GetComponent<dae::RenderComponent>();
		m_StartSourceRect = m_RenderComp->GetSourceRect();
		m_CurrentSourceRect = m_StartSourceRect;
	}

	virtual ~Animation() { }
	Animation(const Animation& other) = delete;
	Animation(Animation&& other) = delete;
	Animation& operator=(const Animation& other) = delete;
	Animation& operator=(Animation&& other) = delete;

private:
	float m_CurrentTime = 0;
	float m_FlipTime;

	int m_CurrentFrame = 0;
	int m_MaxFrames;

	bool m_AnimationOn;

	bool m_LoopAnimation;

	SDL_Rect m_StartSourceRect;
	SDL_Rect m_CurrentSourceRect;
	dae::RenderComponent* m_RenderComp;
};

