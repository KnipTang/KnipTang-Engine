#include <stdexcept>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextObject::TextObject(GameObject* pParent, const std::string& text, std::shared_ptr<Font> font)
	: Component(pParent), m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr)
{ }

void dae::TextObject::Update(const GameObject& /*gameObject*/, float /*deltaTime*/)
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextObject::Render(const GameObject& gameObject) const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = gameObject.GetComponent<dae::Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void dae::TextObject::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}


