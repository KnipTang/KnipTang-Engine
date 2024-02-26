#include <cmath>
#include <string>
#include <iostream>
#include <format>
#include "FpsComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"

dae::FpsComponent::FpsComponent(TextObject* textObject)
	: m_TextObject(textObject)
{
}

void dae::FpsComponent::Update(const GameObject& /*gameObject*/, float deltaTime)
{
	m_FpsTimer += deltaTime;
	m_FrameCount++;
	if (m_FpsTimer >= m_MaxDelay)
	{
		m_CurrentFps = m_FrameCount / m_FpsTimer;

		//Is the SetText to expansive, does it update even if its the same text check if the new fps is not the same as the old one if so skip the settext
		std::string fpsString{ std::format("{:.1f}",  m_CurrentFps) + " FPS" };
		m_TextObject->SetText(fpsString);

		m_FrameCount = 0;
		m_FpsTimer = 0.0f;
	}
}