#include "RotationComponent.h"

#include "GameObject.h"
#include <iostream>

void dae::RotationComponent::Update(float deltaTime)
{
    m_Angle += m_AngularSpeed * deltaTime;

    float x = GetOwner()->GetParent()->GetGameObjectPosition().x + m_Radius * cos(m_Angle);
    float y = GetOwner()->GetParent()->GetGameObjectPosition().y + m_Radius * sin(m_Angle);

    GetOwner()->SetGameObjectPosition(x, y);
}
