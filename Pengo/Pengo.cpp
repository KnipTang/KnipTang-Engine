// Pengo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"


#include <iostream>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "FpsComponent.h"
#include "RotationComponent.h"
#include "Exercise1_ImGui_Component.h"
#include "Exercise2_ImGui_Component.h"
#include "InputManager.h"
#include "GameCommands.h"
#include "Subject.h"
//#include "Achievement.h"
#include "HealthComponent.h"
#include "StateDisplay.h"
#include "ScoreComponent.h"
#include "CollisionComponent.h"
#include "CollisionObserver.h"
#include "SDLSoundSystem.h"
#include "SoundServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SoundCommands.h"
#include <SDL_mixer.h>

// Global access to Achievements object
//dae::CSteamAchievements* g_SteamAchievements = NULL;
//dae::Achievement* g_achievementObserver;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background image
	auto backGround = std::make_unique<dae::GameObject>();
	backGround.get()->AddComponent(new dae::RenderComponent(backGround.get()));
	backGround.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	//
	//DAE logo image
	auto DAElogo = std::make_unique<dae::GameObject>();
	DAElogo.get()->AddComponent(new dae::RenderComponent(DAElogo.get()));
	DAElogo.get()->GetComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	DAElogo.get()->SetGameObjectPosition(216.f, 180.f);

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_unique<dae::GameObject>();
	text.get()->SetGameObjectPosition(80, 20);
	text.get()->AddComponent(new dae::TextObject(text.get(), "Programming 4 Assignment", std::move(font)));

	//FPS
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto FPS = std::make_unique<dae::GameObject>();
	FPS.get()->SetGameObjectPosition(0, 70);
	FPS.get()->AddComponent(new dae::TextObject(FPS.get(), "0FPS", std::move(font)));
	FPS.get()->AddComponent(new dae::FpsComponent(FPS.get(), FPS.get()->GetComponent<dae::TextObject>()));

	//SetParent testSetup
	//go = std::make_shared<dae::GameObject>();
	//auto secondGo = std::make_shared<dae::GameObject>();
	//go.get()->SetGameObjectPosition(8, 8);
	//secondGo.get()->SetGameObjectPosition(10, 5);
	//go.get()->SetParent(secondGo.get(), true);
	//std::cout << secondGo->GetGameObjectPosition().x << '\n' << go->GetGameObjectPosition().x;
	//scene.Add(go);
	//scene.Add(secondGo);

	
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto P1_Explain = std::make_unique<dae::GameObject>();
	P1_Explain.get()->SetGameObjectPosition(0, 100);
	P1_Explain.get()->AddComponent(new dae::TextObject(P1_Explain.get(), "Use the D-Pad to move player 1, X to inflict damage, A and B to pick up pellets", std::move(font)));

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto P2_Explain = std::make_unique<dae::GameObject>();
	P2_Explain.get()->SetGameObjectPosition(0, 120);
	P2_Explain.get()->AddComponent(new dae::TextObject(P2_Explain.get(), "Use WASD to move player 2, C to inflict damage, Z and X to pick up pellets", std::move(font)));

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto Sound_Explain = std::make_unique<dae::GameObject>();
	Sound_Explain.get()->SetGameObjectPosition(50, 200);
	Sound_Explain.get()->AddComponent(new dae::TextObject(Sound_Explain.get(), "Press P to play sound", std::move(font)));


	//P1
	auto P1 = std::make_unique<dae::GameObject>();
	P1.get()->AddComponent(new dae::RenderComponent(P1.get()));
	P1.get()->GetComponent<dae::RenderComponent>()->SetTexture("Pengo.png");
	//P1.get()->GetComponent<dae::RenderComponent>()->SetSourceRecr(32,32,16,16);
	P1.get()->SetGameObjectPosition(200, 200);
	P1.get()->AddComponent(new dae::CollisionComponent(P1.get(), 16.f, 16.f));
	P1.get()->AddComponent(new dae::HealthComponent(P1.get()));
	P1.get()->AddComponent(new dae::ScoreComponent(P1.get()));
	P1.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new dae::CollisionObserver());
	P1.get()->SetTag("Player");

	//auto displayLives{ std::make_shared<dae::GameObject>() };
	//displayLives.get()->SetGameObjectPosition(0, 150);
	//displayLives.get()->SetParent(P1.get(), true);
	//displayLives->AddComponent(new dae::StateDisplay(displayLives.get(), "Lives", P1.get()->GetComponent<dae::HealthComponent>()->GetLives()));
	//scene.Add(displayLives);
	//
	//auto displayPoints{ std::make_shared<dae::GameObject>() };
	//displayPoints.get()->SetGameObjectPosition(0, 170);
	//displayPoints.get()->SetParent(P1.get(), true);
	//displayPoints->AddComponent(new dae::StateDisplay(displayPoints.get(), "Points", P1.get()->GetComponent<dae::ScoreComponent>()->GetPoints()));
	//scene.Add(displayPoints);
	//auto achievementObject{ std::make_shared<dae::GameObject>() };
	//achievementObject.get()->SetParent(P1.get(), true);
	////achievementObject->AddComponent(new dae::Achievement(g_SteamAchievements));
	//scene.Add(achievementObject);
	//g_achievementObserver = new dae::Achievement(g_SteamAchievements);
	//P1.get()->GetComponent<dae::HealthComponent>()->AddObserver(displayLives->GetComponent<dae::StateDisplay>());
	//P1.get()->GetComponent<dae::ScoreComponent>()->AddObserver(displayPoints->GetComponent<dae::StateDisplay>());
	//P1.get()->GetComponent<dae::ScoreComponent>()->AddObserver(g_achievementObserver);

	auto P2 = std::make_unique<dae::GameObject>();
	P2.get()->AddComponent(new dae::RenderComponent(P2.get()));
	P2.get()->GetComponent<dae::RenderComponent>()->SetTexture("Pengo.png");
	P2.get()->SetGameObjectPosition(300, 200);
	P2.get()->AddComponent(new dae::CollisionComponent(P2.get(), 16.f, 16.f));
	P2.get()->AddComponent(new dae::HealthComponent(P2.get()));
	P2.get()->AddComponent(new dae::ScoreComponent(P2.get()));
	P2.get()->AddComponent(new dae::CollisionComponent(P2.get(), 16.f, 16.f));
	P2.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new dae::CollisionObserver());

	//auto background = std::make_shared<dae::GameObject>();
	//background.get()->AddComponent(new dae::RenderComponent(background.get()));
	//background.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
	//background.get()->GetComponent<dae::RenderComponent>()->SetSourceRecr(0, 0, 224, 256);
	//background.get()->SetGameObjectPosition(200, 200);
	////background.get()->AddComponent(new dae::CollisionComponent(background.get(), 16.f, 16.f));
	//scene.Add(background);

	/*
	displayLives = std::make_shared<dae::GameObject>();
	displayLives.get()->SetGameObjectPosition(0, 190);
	displayLives.get()->SetParent(P2.get(), true);
	displayLives->AddComponent(new dae::StateDisplay(displayLives.get(), "Lives", P2.get()->GetComponent<dae::HealthComponent>()->GetLives()));
	scene.Add(displayLives);

	displayPoints = std::make_shared<dae::GameObject>();
	displayPoints.get()->SetGameObjectPosition(0, 210);
	displayPoints.get()->SetParent(P2.get(), true);
	displayPoints->AddComponent(new dae::StateDisplay(displayPoints.get(), "Points", P2.get()->GetComponent<dae::ScoreComponent>()->GetPoints()));
	scene.Add(displayPoints);

	P2.get()->GetComponent<dae::HealthComponent>()->AddObserver(displayLives->GetComponent<dae::StateDisplay>());
	P2.get()->GetComponent<dae::ScoreComponent>()->AddObserver(displayPoints->GetComponent<dae::StateDisplay>());
	P2.get()->GetComponent<dae::ScoreComponent>()->AddObserver(g_achievementObserver);

	//Trash the Cache
	//go = std::make_shared<dae::GameObject>();
	//go.get()->AddComponent(new dae::Exercise1_ImGui_Component(go.get()));
	//go.get()->AddComponent(new dae::Exercise2_ImGui_Component(go.get()));
	//scene.Add(go);
	*/

	//auto& ss = dae::SoundServiceLocator::get_sound_system();
	//ss.play("PinkPanther60.wav", 100);
	//ss.play("test.mp3", 100);

	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P1.get(), P1.get()->GetComponent<dae::ScoreComponent>()));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_A), dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P1.get(), P1.get()->GetComponent<dae::ScoreComponent>()));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_X), dae::InputActionType::IsDown, std::make_unique<dae::Damage>(P1.get(), P1.get()->GetComponent<dae::HealthComponent>()));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), glm::vec3(0, -1, 0), 500.f));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), glm::vec3(0, 1, 0), 500.f));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), glm::vec3(-1, 0, 0), 500.f));
	dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P1.get(), glm::vec3(1, 0, 0), 500.f));
	dae::InputManager::GetInstance().BindCommand(SDLK_w, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(0, -1, 0)));
	dae::InputManager::GetInstance().BindCommand(SDLK_s, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(0, 1, 0)));
	dae::InputManager::GetInstance().BindCommand(SDLK_a, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(-1, 0, 0)));
	dae::InputManager::GetInstance().BindCommand(SDLK_d, dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(1, 0, 0)));
	dae::InputManager::GetInstance().BindCommand(SDLK_z, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P2.get(), P2.get()->GetComponent<dae::ScoreComponent>()));
	dae::InputManager::GetInstance().BindCommand(SDLK_x, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P2.get(), P2.get()->GetComponent<dae::ScoreComponent>()));
	dae::InputManager::GetInstance().BindCommand(SDLK_c, dae::InputActionType::IsDown, std::make_unique<dae::Damage>(P2.get(), P2.get()->GetComponent<dae::HealthComponent>()));
	dae::InputManager::GetInstance().BindCommand(SDLK_p, dae::InputActionType::IsUp, std::make_unique<dae::SoundCommand>());

	scene.Add(std::move(backGround));
	scene.Add(std::move(DAElogo));
	scene.Add(std::move(text));
	scene.Add(std::move(FPS));
	scene.Add(std::move(P1));
	scene.Add(std::move(P2));
	scene.Add(std::move(P1_Explain));
	scene.Add(std::move(P2_Explain));
	scene.Add(std::move(Sound_Explain));
	//dae::InputManager::GetInstance().BindCommand(SDLK_t, dae::InputActionType::IsDown, std::make_unique<dae::Damage>(go.get(), go.get()->GetComponent<dae::HealthComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_x, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(go.get(), go.get()->GetComponent<dae::ScoreComponent>()));

	//if (g_SteamAchievements)
	//	g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
}
int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
	//dae::Minigin engine;
	//engine.Run();
	//return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
