#include "AttackComponent.h"
#include "WallMovementComponent.h"
#include <iostream>

void AttackComponent::Attack()
{
	//m_ObjectInfront->SetGameObjectPosition(5, 5);
	if (m_AttackReady)
	{
		//if(m_ObjectInfront->HasComponent<WallMovementComponent>())
		//{
		//	m_ObjectInfront->GetComponent<WallMovementComponent>()->Move(direction);
		//}
		std::cout << "Ready;'\n";
	}
	else
		std::cout << "NOTReady;'\n";
}
