#include "PengoPlayer.h"
#include "Component.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "MovementComponent.h"
#include "PengoCollisionObserver.h"
#include "InputManager.h"
#include "PlayerCommands.h"

PengoPlayer::PengoPlayer(int posX, int posY)
{
	m_Actor.get()->AddComponent(new dae::RenderComponent(m_Actor.get()));
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
	m_Actor.get()->GetComponent<dae::RenderComponent>()->SetSourceRecr(0, 16 * 4, 16, 16);
	m_Actor.get()->SetGameObjectPosition(static_cast<float>(posX), static_cast<float>(posY));
	m_Actor.get()->AddComponent(new dae::CollisionComponent(m_Actor.get(), 16.f, 16.f));
	m_Actor.get()->AddComponent(new dae::HealthComponent(m_Actor.get()));
	m_Actor.get()->AddComponent(new dae::ScoreComponent(m_Actor.get()));
	m_Actor.get()->AddComponent(new MovementComponent(m_Actor.get()));
	m_Actor.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new PengoCollisionObserver(m_Actor.get()));
	m_Actor.get()->SetTag("Player");

    //m_State = new MoveState{};

	dae::InputManager::GetInstance().BindCommand(SDLK_w, dae::InputActionType::IsDown, std::make_unique<dae::Movement>(m_Actor.get(), this, Controlls::UP));
	dae::InputManager::GetInstance().BindCommand(SDLK_s, dae::InputActionType::IsDown, std::make_unique<dae::Movement>(m_Actor.get(), this, Controlls::DOWN));
	dae::InputManager::GetInstance().BindCommand(SDLK_a, dae::InputActionType::IsDown, std::make_unique<dae::Movement>(m_Actor.get(), this, Controlls::LEFT));
	dae::InputManager::GetInstance().BindCommand(SDLK_d, dae::InputActionType::IsDown, std::make_unique<dae::Movement>(m_Actor.get(), this, Controlls::RIGHT));
}

void PengoPlayer::HandleInput(Controlls /*control*/)
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
	//PengoState* newState = m_State->HandleInput(control);
    //if (newState != nullptr)
    //    m_State = newState;
}
