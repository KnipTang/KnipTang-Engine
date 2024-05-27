#include "Level.h"
#include <fstream> 
#include <iostream>
#include <sstream> 
#include "Wall.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "PengoComponent.h"
#include "PengoCollisionObserver.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include <InputManager.h>
#include "PlayerCommands.h"
#include "InFrontViewComponent.h"
#include "InFrontObserver.h"
#include "AttackComponent.h"
#include "WallMovementComponent.h"
#include "WallCollisionObserver.h"
#include "EnemyComponent.h"
#include "EnemyMovementAIComponent.h"
#include "EnemyCollisionObserver.h"
#include "WallComponent.h"

Level::Level(std::string filePath) : m_FilePath(filePath)
{

}

std::vector<std::unique_ptr<dae::GameObject>> Level::LoadLevel()
{
    std::ifstream inputFile(m_FilePath);
    std::string line;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) 
        {
            HandleLine(line);
            m_CurrentRow++;
        }
        inputFile.close();
    }
    else {
        std::cerr << "Unable to open file";
    }
    return std::move(m_GameObjects);
}

void Level::HandleLine(std::string line)
{
    std::stringstream ss(line);
    std::string element;
    std::vector<std::string> elements;
    while (std::getline(ss, element, ',')) {
        elements.push_back(element);
    }

    for (const auto& elem : elements)
    {
        HandleElement(elem);
        m_CurrentColum++;
    }
    m_CurrentColum = 0;
    //Printing
    {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

void Level::HandleElement(std::string element)
{
    int elementNr = std::stoi(element);

    m_PosX = static_cast<float>(m_MapBorder + m_Element * m_CurrentColum);
    m_PosY = static_cast<float>(m_MapBorder + m_Element * m_CurrentRow);

    switch (elementNr)
    {
    case 0: // Nothing
        break;
    case 1: // Player
        PlacePlayer();
        break;
    case 2: // Wall
        PlaceWall();
        break;
    case 3: // Enemy
        PlaceEnemy();
        break;
    default:
        break;
    }
}

void Level::PlacePlayer()
{
    auto P1 = std::make_unique<dae::GameObject>();

    P1.get()->AddComponent(new PengoComponent(P1.get()));
    P1.get()->AddComponent(new AttackComponent(P1.get()));
    P1.get()->AddComponent(new dae::RenderComponent(P1.get()));
    P1.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    P1.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(16 * 0, 16 * 0, 16, 16);
    P1.get()->AddComponent(new Animation(P1.get()));
    P1.get()->SetGameObjectPosition(m_PosX, m_PosY);
    P1.get()->AddComponent(new dae::CollisionComponent(P1.get(), 1.f, 1.f, 8.f, 8.f));
    P1.get()->AddComponent(new dae::HealthComponent(P1.get()));
    P1.get()->AddComponent(new dae::ScoreComponent(P1.get()));
    P1.get()->AddComponent(new MovementComponent(P1.get()));
    P1.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new PengoCollisionObserver(P1.get()));
    P1.get()->SetTag("Player");

    auto InFront = std::make_unique<dae::GameObject>();
    InFront.get()->AddComponent(new dae::RenderComponent(InFront.get()));
    InFront.get()->SetGameObjectPosition(0, 16.f);
    InFront.get()->GetComponent<dae::RenderComponent>()->SetTexture("Red.png");
    InFront.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(16 * 0, 16 * 0, 5, 5);
    InFront.get()->AddComponent(new dae::CollisionComponent(InFront.get(), 1.f, 1.f));
    InFront.get()->AddComponent(new InFrontViewComponent(InFront.get()));
    InFront.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new InFrontObserver(InFront.get()));

    InFront.get()->SetParent(P1.get(), false);
    

    dae::InputManager::GetInstance().BindCommand(SDLK_w, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(SDLK_s, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(SDLK_a, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(SDLK_d, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(SDLK_e, dae::InputActionType::IsPressed, std::make_unique<dae::Attack>(P1.get(), Controlls::ATTACK));

    dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsPressed, std::make_unique<dae::Attack>(P1.get(), Controlls::ATTACK));

    m_GameObjects.emplace_back(std::move(P1));    
    m_GameObjects.emplace_back(std::move(InFront));
}

void Level::PlaceWall()
{
    auto wall = std::make_unique<dae::GameObject>();

    wall.get()->AddComponent(new WallComponent(wall.get()));
    wall.get()->AddComponent(new dae::RenderComponent(wall.get()));
    wall.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
    wall.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(708, 0, 16, 16);
    wall.get()->SetGameObjectPosition(m_PosX, m_PosY);
    wall.get()->AddComponent(new dae::CollisionComponent(wall.get(), 16, 16));
    wall.get()->AddComponent(new WallMovementComponent(wall.get()));
    //wall.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new WallCollisionObserver(wall.get()));
    wall.get()->SetTag("Wall");

    m_GameObjects.emplace_back(std::move(wall));
}

void Level::PlaceEnemy()
{
    auto enemy = std::make_unique<dae::GameObject>();

    enemy.get()->AddComponent(new EnemyComponent(enemy.get()));
    enemy.get()->AddComponent(new EnemyMovementAIComponent(enemy.get()));
    enemy.get()->AddComponent(new dae::RenderComponent(enemy.get()));
    enemy.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    enemy.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 9, 16, 16);
    enemy.get()->SetGameObjectPosition(static_cast<float>(m_PosX), static_cast<float>(m_PosY));
    enemy.get()->AddComponent(new dae::CollisionComponent(enemy.get(), 16.f, 16.f));
    enemy.get()->AddComponent(new dae::HealthComponent(enemy.get()));
    enemy.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(enemy.get()));
    enemy.get()->SetTag("Enemy");

    m_GameObjects.emplace_back(std::move(enemy));
}
