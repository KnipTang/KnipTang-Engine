#pragma once
#include <string>
#include <memory>
#include "Component.h"
namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextObject final : public Component
	{
	public:
		void Update(float deltaTime) override;
		void LateUpdate(float /*deltaTime*/) override {};
		void FixedUpdate(float /*fixedTimeStep*/) override {};
		void Render() const override;

		void SetText(const std::string& text);

		//std::shared_ptr<Texture2D> GetTexture() const { return m_textTexture; };

		explicit TextObject(GameObject* pParent, const std::string& text, std::shared_ptr<Font> font);
		~TextObject() override = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;
	};
}
