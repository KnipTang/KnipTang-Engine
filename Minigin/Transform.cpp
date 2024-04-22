#include "Transform.h"

#include "GameObject.h"

void dae::Transform::SetWorldPosition(const float x, const float y, const float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}
void dae::Transform::SetWorldPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = 0;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (unsigned int i = 0; i < static_cast<unsigned int>(GetOwner()->GetChildCount()); i++)
	{
		GetOwner()->GetChildAt(i)->GetTransform()->SetPositionDirty();
	}
}

const glm::vec3 dae::Transform::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		m_PositionIsDirty = false;
		if (GetOwner() == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = GetOwner()->GetParent()->GetGameObjectPosition() + m_LocalPosition;
	}
}