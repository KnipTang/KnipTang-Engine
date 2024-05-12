#include "PengoComponent.h"


void PengoComponent::Update(float)
{
    if (m_State != nullptr)
        m_State->Update();
}

void PengoComponent::HandleInput(Controlls control)
{
    /*
    switch (control)
    {
    case Controlls::UP:
        std::cout << "UP" << std::endl;
        // Handle UP control logic
        break;
    case Controlls::DOWN:
        std::cout << "DOWN" << std::endl;
        // Handle DOWN control logic
        break;
    case Controlls::LEFT:
        std::cout << "LEFT" << std::endl;
        // Handle LEFT control logic
        break;
    case Controlls::RIGHT:
        std::cout << "RIGHT" << std::endl;
        // Handle RIGHT control logic
        break;
    case Controlls::ATTACK:
        std::cout << "ATTACK" << std::endl;
        // Handle ATTACK control logic
        break;
    default:
        std::cout << "Unknown control" << std::endl;
        break;
    }
    */

    std::unique_ptr<PengoState> newState = m_State->HandleInput(GetOwner(), control);
    if (newState != nullptr)
    {
        m_State = std::move(newState);
        m_State->Enter(GetOwner());
    }
}
