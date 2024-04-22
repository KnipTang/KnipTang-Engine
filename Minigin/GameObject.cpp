#include <string>
#include "GameObject.h"

#include <iostream>

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
	//const auto& pos = m_transform.GetWorldPosition();
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(Component* component)
{
	m_pComponents.emplace_back(component);
}

void dae::GameObject::RemoveComponent(Component* component)
{
	auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(),
		[component](const std::unique_ptr<Component>& ptr) { return ptr.get() == component; });

	if (it != m_pComponents.end()) {
		m_pComponents.erase(it);
	}
}

void dae::GameObject::RemoveAllComponent()
{
	for (const auto& component : m_pComponents)
	{
		RemoveComponent(component.get());
	}
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	//Check if the new parent is valid (not itself or one of its children)
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
	//Remove itself from the previous parent
	if (m_pParent) 
		m_pParent->RemoveChild(this);

	//Set the given parent on itself.  // Not sure if the way of assigning the parent is correct
	m_pParent = parent;

	//Add itself as a child to the given parent
	if (m_pParent) 
		m_pParent->AddChild(this);
}

void dae::GameObject::RemoveAllChildren()
{
	for (const auto& children : m_pChildren)
	{
		children->RemoveAllComponent();
		RemoveChild(children);
	}
}

//todo not compleet
void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

//todo not compleet
void dae::GameObject::RemoveChild(GameObject* child)
{
	//child->SetParent(nullptr, false);
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
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