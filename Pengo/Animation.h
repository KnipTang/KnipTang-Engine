#pragma once
#include "Component.h"
#include "RenderComponent.h"

class Animation : public dae::Component
{
public:
	Animation(dae::GameObject* gameObject, bool animationOn = false, int maxFrames = 1, bool loopAnimation = false, bool resetWhenDone = false, float flipTime = 0.25f);

	~Animation() override = default;
	Animation(const Animation& other) = delete;
	Animation(Animation&& other) = delete;
	Animation& operator=(const Animation& other) = delete;
	Animation& operator=(Animation&& other) = delete;

	void Update(float deltaTime) override;

	void SetStartSourceRect(SDL_Rect startSourceRect);
	SDL_Rect GetStartSourceRect() { return m_StartSourceRect; }

	void SetCurrentSourceRect(SDL_Rect currentSourceRect);

	SDL_Rect GetCurrentSourceRect() { return m_CurrentSourceRect; }

	void ToggleAnimation(bool animation) { m_AnimationOn = animation; };
	bool IsAnimating() { return m_AnimationOn; }

	void SetFlipTime(float flipTime) { m_FlipTime = flipTime; }
	float GetFlipTime() { return m_FlipTime; }

	void SetMaxFrames(int maxFrames) { m_MaxFrames = maxFrames; }
	int GetMaxFrames() { return m_MaxFrames; }

	void ToggleLooping(bool loopValue) { m_LoopAnimation = loopValue; }
	void ToggleResetWhenDone(bool resetWhenDone) { m_ResetWhenDone = resetWhenDone; }

private:
	float m_CurrentTime = 0;
	float m_FlipTime;

	int m_CurrentFrame = 0;
	int m_MaxFrames;

	bool m_AnimationOn;

	bool m_LoopAnimation;
	bool m_ResetWhenDone;

	SDL_Rect m_StartSourceRect;
	SDL_Rect m_CurrentSourceRect;
	dae::RenderComponent* m_RenderComp;
};
