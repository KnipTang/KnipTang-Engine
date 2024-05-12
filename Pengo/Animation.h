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

	void SetCurrentSourceRect(SDL_Rect currentSourceRect) 
	{ 
		m_CurrentSourceRect = currentSourceRect; 
		if (GetOwner()->HasComponent<dae::RenderComponent>())
		{
			dae::RenderComponent* renderComp = GetOwner()->GetComponent<dae::RenderComponent>();
			renderComp->SetSourceRect(m_CurrentSourceRect.x, m_CurrentSourceRect.y, m_CurrentSourceRect.w, m_CurrentSourceRect.h);
		}
	}
	SDL_Rect GetCurrentSourceRect() { return m_CurrentSourceRect; }

	Animation(dae::GameObject* gameObject) : dae::Component(gameObject) 
	{ 
		m_MaxFrames = 1; 

		m_CurrentSourceRect = GetOwner()->GetComponent<dae::RenderComponent>()->GetSourceRect();
	}

	void ToggleAnimation(bool animation) { m_AnimationOn = animation; };

	virtual ~Animation() { }
	Animation(const Animation& other) = delete;
	Animation(Animation&& other) = delete;
	Animation& operator=(const Animation& other) = delete;
	Animation& operator=(Animation&& other) = delete;

private:
	float m_Time = 0;
	float m_FlipTime = 0.25f;

	int m_CurrentFrame = 0;
	int m_MaxFrames;

	bool m_AnimationOn;

	SDL_Rect m_CurrentSourceRect;
};

