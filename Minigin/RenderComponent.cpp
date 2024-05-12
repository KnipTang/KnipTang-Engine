#include "RenderComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextObject.h"
#include "Texture2D.h"
void dae::RenderComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_texture, GetOwner()->GetGameObjectPosition().x, GetOwner()->GetGameObjectPosition().y, m_SourceRect);
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetSourceRect(const int x, const int y, const int widthSrc, const int heightSrc)
{
	m_SourceRect.x = x;
	m_SourceRect.y = y;
	m_SourceRect.w = widthSrc;
	m_SourceRect.h = heightSrc;
}

dae::RenderComponent::RenderComponent(GameObject* gameObject) :
	Component(gameObject)
{
	//SDL_Rect src{ 0, 0, -1, -1 };
	//m_SourceRect = src;
}
