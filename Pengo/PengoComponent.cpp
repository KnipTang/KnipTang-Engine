#include "PengoComponent.h"

void PengoComponent::Update(float deltaTime)
{
    if (m_State != nullptr)
        m_State->Update(deltaTime);
}

void PengoComponent::HandleInput(Controlls control)
{
    std::unique_ptr<PengoState> newState = m_State->HandleInput(GetOwner(), control);
    if (newState != nullptr)
    {
        m_State = std::move(newState);
    }
}
