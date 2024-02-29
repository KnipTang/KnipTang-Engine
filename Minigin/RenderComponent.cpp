#include "RenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TextObject.h"

void dae::RenderComponent::Render() const
{
	if(GetOwner()->GetParent()->HasComponent<dae::Transform>())
		Renderer::GetInstance().RenderTexture(*m_texture, GetOwner()->GetParent()->GetComponent<dae::Transform>()->GetWorldPosition().x, GetOwner()->GetParent()->GetComponent<dae::Transform>()->GetWorldPosition().y);
	else
		Renderer::GetInstance().RenderTexture(*m_texture, 0, 0);
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}
