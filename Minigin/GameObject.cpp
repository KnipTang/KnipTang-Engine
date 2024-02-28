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

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_pParent.get() == parent)
		return;
	if (parent == nullptr)
		m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetWorldPosition() - parent->m_Transform.GetWorldPosition());
		m_Transform.SetPositionDirty();
	}
	if (m_pParent.get()) m_pParent.get()->RemoveChild(this);

	m_pParent.reset(parent);

	if (m_pParent.get()) m_pParent.get()->AddChild(this);

}

bool dae::GameObject::IsChild(GameObject* potentialChild) const
{
	if (!potentialChild)
		return false;

	auto it = std::find_if(m_pChildren.begin(), m_pChildren.end(),
		[potentialChild](const std::unique_ptr<GameObject>& child) {
			return child.get() == potentialChild;
		});

	return it != m_pChildren.end();
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}
