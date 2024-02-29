#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "TextObject.h"

namespace dae
{
	class TextObject;
	class GameObject;
	class Renderer;

	class FpsComponent final: public Component
	{
	public:
		void Update(float deltaTime) override;
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override {}

		float GetFps() const { return m_CurrentFps; };

		explicit FpsComponent(GameObject* pParent, TextObject* textObject);
		~FpsComponent() override { m_TextObject = nullptr; delete m_TextObject; };
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;
	private:
		//int or float?
		float m_FrameCount = 0;
		float m_FpsTimer = 0.0f;

		float m_CurrentFps = 0.0f;

		float m_MaxDelay = 1.0f;

		TextObject* m_TextObject;
	};
}
