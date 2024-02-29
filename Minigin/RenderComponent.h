#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject;
	class Renderer;

	class RenderComponent final: public Component
	{
	public:
		void Update(float /*deltaTime*/) override {}
		void LateUpdate(float /*deltaTime*/) override {}
		void FixedUpdate(float /*fixedTimeStep*/) override {}
		void Render() const override;

		void SetTexture(const std::string& filename);
		//void SetTexture(std::shared_ptr<Texture2D> filename) { m_texture = filename; };

		explicit RenderComponent(GameObject* pParent) : Component(pParent) {}
		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}
