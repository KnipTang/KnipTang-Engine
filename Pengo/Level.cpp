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
#include <Xinput.h>

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
    m_GameObjects.clear();

    LoadBorder();

    std::ifstream inputFile(m_FilePath);
    std::string line;
    m_CurrentRow = 0;

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
    case 5: // Player2 (CoOp)
        PlacePlayer2();
        break;
    case 6: // PlayableEnemy (Versus)
        PlacePlayableEnemy();
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
    player.get()->AddComponent(new dae::CollisionComponent(player.get(), 4.f, 4.f, 6.f, 6.f));
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
    player.get()->AddComponent(new dae::CollisionComponent(player.get(), 4.f, 4.f, 6.f, 6.f));
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

void Level::PlacePlayableEnemy()
{
    auto player = std::make_unique<dae::GameObject>();

    player.get()->AddComponent(new dae::RenderComponent(player.get()));
    player.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
    player.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16 * 8, 16, 16);
    player.get()->SetGameObjectPosition(m_PosX, m_PosY);
    player.get()->AddComponent(new Animation(player.get(), true, 2, true));
    player.get()->AddComponent(new EnemyComponent(player.get()));
    player.get()->GetComponent<EnemyComponent>()->SetState(std::make_unique<SpawningState>(player.get()));
    player.get()->AddComponent(new dae::CollisionComponent(player.get(), 14.f, 14.f, 1.f, 1.f));
    player.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new EnemyCollisionObserver(player.get()));
    player.get()->AddComponent(new MovementComponent(player.get()));
    player.get()->SetLayer("Enemy");
    player.get()->SetTag("PlayableEnemy");

    Player2Bindings(player.get());

    m_GameObjects.emplace_back(std::move(player));
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
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_W, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_S, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_A, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_D, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_E, dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));

    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(DWORD(0),WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));
}

void Level::Player2Bindings(dae::GameObject* player)
{
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_UP, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_DOWN, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_LEFT, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_RIGHT, dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_RSHIFT, dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));

    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::UP));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::DOWN));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::LEFT));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<Movement>(player, Controlls::RIGHT));
    dae::InputManager::GetInstance().BindCommand(DWORD(1), WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsPressed, std::make_unique<Attack>(player, Controlls::ATTACK));
}

void Level::LoadBorder()
{
    std::vector<std::unique_ptr<dae::GameObject>> borders;
    {
        auto border = std::make_unique<dae::GameObject>();
        border.get()->SetGameObjectPosition(0, Config::MENUTOP_SIZE);
        border.get()->AddComponent(new dae::CollisionComponent(border.get(), 224.f, 8.f));
        border.get()->SetLayer("Wall");
        borders.emplace_back(std::move(border));

        border = std::make_unique<dae::GameObject>();
        border.get()->SetGameObjectPosition(0, Config::MENUTOP_SIZE);
        border.get()->AddComponent(new dae::CollisionComponent(border.get(), 8.f, 256.f));
        border.get()->SetLayer("Wall");
        borders.emplace_back(std::move(border));

        border = std::make_unique<dae::GameObject>();
        border.get()->SetGameObjectPosition(0, Config::MENUTOP_SIZE + 248.f);
        border.get()->AddComponent(new dae::CollisionComponent(border.get(), 224.f, 8.f));
        border.get()->SetLayer("Wall");
        borders.emplace_back(std::move(border));

        border = std::make_unique<dae::GameObject>();
        border.get()->SetGameObjectPosition(216.f, Config::MENUTOP_SIZE);
        border.get()->AddComponent(new dae::CollisionComponent(border.get(), 8.f, 256.f));
        border.get()->SetLayer("Wall");
        borders.emplace_back(std::move(border));
    }

    for (auto& bord : borders)
    {
        m_GameObjects.emplace_back(std::move(bord));
    }
}
