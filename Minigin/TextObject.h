#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "Texture2D.h"
#include "Font.h"
namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public Component
	{
	public:
		TextObject(GameObject* gameObject, const std::string& text, std::unique_ptr<Font> font);

		~TextObject() override = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::unique_ptr<Font> m_font;
		std::unique_ptr<Texture2D> m_textTexture;
	};
}
