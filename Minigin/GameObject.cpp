#include "GameObject.h"
#include <algorithm>

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->LateUpdate(deltaTime);
	}

	for (auto& components : m_pComponents)
	{
		if (components == nullptr) continue;
		if (components.get()->IsRemoveComponentTrue())
		{
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), components), m_pComponents.end());
		}
	}

	for (auto& components : m_pPendingComponents) {
		m_pComponents.emplace_back(std::move(components));
	}
	m_pPendingComponents.clear();
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
	for (const auto& component : m_pComponents)
	{
		component->FixedUpdate(fixedTimeStep);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(Component* component)
{
	m_pPendingComponents.emplace_back(component);
}

void dae::GameObject::RemoveComponent(Component* component)
{
	component->RemoveComponent();
}

void dae::GameObject::RemoveAllComponent()
{
	for (auto& components : m_pComponents)
	{
		components.get()->RemoveComponent();
	}
	m_pPendingComponents.clear();
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_pParent == parent)
		return;

	if (parent == nullptr)
		m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());
	else
	{
		if (keepWorldPosition)
		{
			m_Transform.SetLocalPosition(m_Transform.GetWorldPosition() - parent->m_Transform.GetWorldPosition());
		}
		m_Transform.SetPositionDirty();
	}
	if (m_pParent) 
		m_pParent->RemoveChild(this);

	m_pParent = parent;

	if (m_pParent) 
		m_pParent->AddChild(this);
}

void dae::GameObject::RemoveAllChildren()
{
	for (const auto& children : m_pChildren)
	{
		RemoveChild(children);
	}
}

void dae::GameObject::RemoveGameObject()
{
	m_RemoveGameObject = true;
	for (const auto& children : m_pChildren)
	{
		children->RemoveGameObject();
	}
	if (GetParent() != nullptr)
	{
		GetParent()->RemoveChild(this);
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_pChildren, child);
}

bool dae::GameObject::IsChild(GameObject* potentialChild) const
{
	if (!potentialChild)
		return false;
	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(),
		[potentialChild](GameObject* child) {
			return child == potentialChild;
		});
	return it != m_pChildren.end();
}