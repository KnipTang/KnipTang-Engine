#include "Transform.h"

#include "GameObject.h"

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
void dae::Transform::SetPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = 0;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
	SetPositionDirty();
}

const glm::vec3 dae::Transform::GetWorldPosition() const
{
	if (GetOwner()->GetParent() != nullptr)
		return GetOwner()->GetParent()->GetWorldPosition() + GetLocalPosition();
	return GetLocalPosition();
}
