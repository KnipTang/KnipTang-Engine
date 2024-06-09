#pragma once
#include "Component.h"
#include "TextObject.h"

class TextObject;
class GameObject;
class Renderer;
class FpsComponent final : public dae::Component
{
public:
	FpsComponent(dae::GameObject* gameObject, dae::TextObject* textObject);
	~FpsComponent() override { m_TextObject = nullptr; delete m_TextObject; }

	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) = delete;

	void Update(float deltaTime) override;

	float GetFps() const { return m_CurrentFps; }

private:
	float m_FrameCount = 0;
	float m_FpsTimer = 0.0f;

	float m_CurrentFps = 0.0f;

	float m_MaxDelay = 1.0f;

	dae::TextObject* m_TextObject;
};
