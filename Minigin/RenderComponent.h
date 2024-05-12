#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Component.h"
#include "Renderer.h"
#include "Texture2D.h"
namespace dae
{
	class Texture2D;
	class GameObject;
	class Renderer;

	class RenderComponent final: public Component
	{
	public:
		void Update(float /*deltaTime*/) override {}
		void LateUpdate(float /*deltaTime*/) override {};
		void FixedUpdate(float /*fixedTimeStep*/) override {};
		void Render() const override;

		void SetTexture(const std::string& filename);

		void SetSourceRect(const int x, const int y, const int widthSrc, const int heightSrc);
		SDL_Rect GetSourceRect() { return m_SourceRect; }

		RenderComponent(GameObject* gameObject);
		~RenderComponent() override {}
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		std::unique_ptr<Texture2D> m_texture{};
		SDL_Rect m_SourceRect{0,0,-1,-1};
	};
}
