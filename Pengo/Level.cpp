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
#include "GameConfig.h"
#include "EnemySpawnComponent.h"
#include "SoundCommands.h"
#include "StateDisplay.h"

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
    m_PosY = static_cast<float>(Config::MENUTOP_SIZE + m_MapBorder + m_Element * m_CurrentRow);

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
        PlaceEnemyWall();
        break;
    case 4: // HardWall
        PlaceHardWall();
        break;
    case 5: // Player2
        PlacePlayer2();
        break;
    default:
        break;
    }
}

void Level::PlacePlayer()
{
    auto player = std::make_unique<dae::GameObject>();

    player.get()->AddComponent(new PengoComponent(player.get()));
    player.get()->AddComponent(new AttackComponent(player.get()));
    player.get()->AddComponent(new dae::RenderComponent(player.get()));
    player.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    player.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(16 * 0, 16 * 0, 16, 16);
    player.get()->AddComponent(new Animation(player.get(), false, 1, true));
    player.get()->SetGameObjectPosition(m_PosX, m_PosY);
    player.get()->AddComponent(new dae::CollisionComponent(player.get(), 1.f, 1.f, 8.f, 8.f));
    player.get()->AddComponent(new HealthComponent(player.get(), 4));
    player.get()->AddComponent(new MovementComponent(player.get()));
    player.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new PengoCollisionObserver(player.get()));
    player.get()->SetLayer("Player");
    player.get()->SetTag("Player1");

    auto InFront = std::make_unique<dae::GameObject>();
    InFront.get()->SetGameObjectPosition(0, 16.f);
    InFront.get()->AddComponent(new dae::CollisionComponent(InFront.get(), 1.f, 1.f));
    InFront.get()->AddComponent(new InFrontViewComponent(InFront.get()));
    InFront.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new InFrontObserver(InFront.get()));

    InFront.get()->SetParent(player.get(), false);

    Player1Bindings(player.get());

    m_GameObjects.emplace_back(std::move(player));    
    m_GameObjects.emplace_back(std::move(InFront));
}

void Level::PlacePlayer2()
{
    auto player = std::make_unique<dae::GameObject>();

    player.get()->AddComponent(new PengoComponent(player.get()));
    player.get()->AddComponent(new AttackComponent(player.get()));
    player.get()->AddComponent(new dae::RenderComponent(player.get()));
    player.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    player.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(16 * 0, 16 * 0, 16, 16);
    player.get()->AddComponent(new Animation(player.get(), false, 1, true));
    player.get()->SetGameObjectPosition(m_PosX, m_PosY);
    player.get()->AddComponent(new dae::CollisionComponent(player.get(), 1.f, 1.f, 8.f, 8.f));
    player.get()->AddComponent(new HealthComponent(player.get(), 4));
    player.get()->AddComponent(new MovementComponent(player.get()));
    player.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new PengoCollisionObserver(player.get()));
    player.get()->SetLayer("Player");
    player.get()->SetTag("Player2");

    auto InFront = std::make_unique<dae::GameObject>();
    InFront.get()->SetGameObjectPosition(0, 16.f);
    InFront.get()->AddComponent(new dae::CollisionComponent(InFront.get(), 1.f, 1.f));
    InFront.get()->AddComponent(new InFrontViewComponent(InFront.get()));
    InFront.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new InFrontObserver(InFront.get()));

    InFront.get()->SetParent(player.get(), false);

    Player2Bindings(player.get());

    m_GameObjects.emplace_back(std::move(player));
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
    wall.get()->AddComponent(new Animation(wall.get(), false, 5));
    wall.get()->AddComponent(new dae::CollisionComponent(wall.get(), 16, 16));
    wall.get()->AddComponent(new WallMovementComponent(wall.get()));
    //wall.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new WallCollisionObserver(wall.get()));
    wall.get()->SetLayer("Wall");
    wall.get()->SetTag("NormalWall");

    m_GameObjects.emplace_back(std::move(wall));
}

void Level::PlaceEnemyWall()
{
    auto wall = std::make_unique<dae::GameObject>();

    wall.get()->AddComponent(new WallComponent(wall.get()));
    wall.get()->AddComponent(new WallMovementComponent(wall.get()));
    wall.get()->AddComponent(new EnemySpawnComponent(wall.get()));
    wall.get()->AddComponent(new dae::RenderComponent(wall.get()));
    wall.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
    wall.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(708, 0, 16, 16);
    wall.get()->SetGameObjectPosition(m_PosX, m_PosY);
    wall.get()->AddComponent(new Animation(wall.get(), true, 1, false, true, 1.f));
    wall.get()->AddComponent(new dae::CollisionComponent(wall.get(), 16, 16));
    wall.get()->SetLayer("Wall");
    wall.get()->SetTag("EnemyWall");

    m_GameObjects.emplace_back(std::move(wall));
}

void Level::PlaceHardWall()
{
    auto wall = std::make_unique<dae::GameObject>();

    wall.get()->AddComponent(new WallComponent(wall.get()));
    wall.get()->AddComponent(new dae::RenderComponent(wall.get()));
    wall.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
    wall.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(708, 16, 16, 16);
    wall.get()->SetGameObjectPosition(m_PosX, m_PosY);
    wall.get()->AddComponent(new dae::CollisionComponent(wall.get(), 16, 16));
    wall.get()->AddComponent(new WallMovementComponent(wall.get()));
    wall.get()->SetLayer("Wall");
    wall.get()->SetTag("HardWall");

    m_GameObjects.emplace_back(std::move(wall));
}

void Level::Player1Bindings(dae::GameObject* player)
{
    dae::InputManager::GetInstance().BindCommand(SDLK_w, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(SDLK_s, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(SDLK_a, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(SDLK_d, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(SDLK_e, dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));
    dae::InputManager::GetInstance().BindCommand(SDLK_m, dae::InputActionType::IsUp, std::make_unique<dae::SoundMuteCommand>());

    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));
}

void Level::Player2Bindings(dae::GameObject* player)
{
    dae::InputManager::GetInstance().BindCommand(SDLK_i, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(SDLK_k, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(SDLK_j, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(SDLK_l, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(SDLK_o, dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));

    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));
}