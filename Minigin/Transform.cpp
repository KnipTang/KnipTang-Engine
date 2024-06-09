#include "Transform.h"
#include "GameObject.h"

void dae::Transform::SetWorldPosition(const float x, const float y, const float z)
{
	SetLocalPosition(glm::vec3{ x, y, z });
}
void dae::Transform::SetWorldPosition(const float x, const float y)
{
	SetLocalPosition(glm::vec3{ x, y, 0 });
}

void dae::Transform::SetWorldPosition(glm::vec3 pos)
{
	SetLocalPosition(pos);
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
		if (GetOwner()->GetParent() == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = GetOwner()->GetParent()->GetGameObjectPosition() + m_LocalPosition;
	}
}