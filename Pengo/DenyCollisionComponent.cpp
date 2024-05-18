#include "DenyCollisionComponent.h"
#include "GameObject.h"
#include "GameConfig.h"

void BlockCollisionCheckComponent::Update(float )
{
	//if (!m_Testing)
	//{
	//	m_StartPos = GetOwner()->GetTransform()->GetWorldPosition();
	//	GetOwner()->SetGameObjectPosition(m_StartPos.x + 1 * m_Direction.x, m_StartPos.y + 1 * m_Direction.y);
	//}
	//else
	//{
	//	GetOwner()->SetGameObjectPosition(m_StartPos.x, m_StartPos.y);
	//}
	//
	//m_Testing = !m_Testing;
}

void BlockCollisionCheckComponent::LateUpdate(float )
{
	//GetOwner()->SetGameObjectPosition(m_StartPos.x, m_StartPos.y);
}

bool BlockCollisionCheckComponent::CheckBlockCollision()
{


	return false;
}


