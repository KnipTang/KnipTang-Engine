#include <string>
#include "GameObject.h"

void dae::GameObject::Update(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->Update(*this, deltaTime);
	}
}

void dae::GameObject::LateUpdate(float deltaTime)
{
	for (const auto& component : m_pComponents)
	{
		component->LateUpdate(*this, deltaTime);
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
	//const auto& pos = m_transform.GetPosition();
	for (const auto& component : m_pComponents)
	{
		component->Render(*this);
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
