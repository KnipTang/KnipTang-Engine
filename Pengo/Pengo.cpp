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
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "RotationComponent.h"
#include "InputManager.h"
#include "Subject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "CollisionComponent.h"
#include "PengoCollisionObserver.h"
#include "SDLSoundSystem.h"
#include "SoundCommands.h"
#include "PlayerCommands.h"
#include "FpsComponent.h"
#include "MovementComponent.h"
#include "PengoState.h"
#include "PengoComponent.h"
#include "Wall.h"
#include "Enemy.h"
#include "Animation.h"
#include "EndScreenComponent.h"
#include "Level.h"
#include "GameConfig.h"
#include "LoggingSoundSystem.h"
#include "TimerComponent.h"
#include "HighScoreComponent.h"

void load()
{
	auto startScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	
	auto backGroundStartScreen = std::make_unique<dae::GameObject>();
	backGroundStartScreen.get()->AddComponent(new dae::RenderComponent(backGroundStartScreen.get()));
	backGroundStartScreen.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	backGroundStartScreen.get()->AddComponent(new dae::TextObject(backGroundStartScreen.get(), "STARTSCREEN", std::move(font)));

	dae::InputManager::GetInstance().BindCommand(SDLK_p, dae::InputActionType::IsUp, std::make_unique<StartGame>(backGroundStartScreen.get()));

	startScene->Add(std::move(backGroundStartScreen));
	dae::SceneManager::GetInstance().LoadScene("StartScreen");

	auto scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//Background image
	auto backGround = std::make_unique<dae::GameObject>();
	backGround.get()->AddComponent(new dae::RenderComponent(backGround.get()));
	backGround.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	//
	//DAE logo image
	auto DAElogo = std::make_unique<dae::GameObject>();
	DAElogo.get()->AddComponent(new dae::RenderComponent(DAElogo.get()));
	DAElogo.get()->GetComponent<dae::RenderComponent>()->SetTexture("logo.tga");
	DAElogo.get()->SetGameObjectPosition(216, 180);
	
	//Text
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto text = std::make_unique<dae::GameObject>();
	text.get()->SetGameObjectPosition(80, 20);
	text.get()->AddComponent(new dae::TextObject(text.get(), "Programming 4 Assignment", std::move(font)));
	
	//FPS
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto FPS = std::make_unique<dae::GameObject>();
	FPS.get()->SetGameObjectPosition(100, 16);
	FPS.get()->AddComponent(new dae::TextObject(FPS.get(), "0FPS", std::move(font)));
	FPS.get()->AddComponent(new dae::FpsComponent(FPS.get(), FPS.get()->GetComponent<dae::TextObject>()));

	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	//auto P1_Explain = std::make_unique<dae::GameObject>();
	//P1_Explain.get()->SetGameObjectPosition(0, 100);
	//P1_Explain.get()->AddComponent(new dae::TextObject(P1_Explain.get(), "Use the D-Pad to move m_Player 1, X to inflict damage, A and B to pick up pellets", std::move(font)));
	//
	//font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	//auto P2_Explain = std::make_unique<dae::GameObject>();
	//P2_Explain.get()->SetGameObjectPosition(0, 120);
	//P2_Explain.get()->AddComponent(new dae::TextObject(P2_Explain.get(), "Use WASD to move m_Player 2, C to inflict damage, Z and X to pick up pellets", std::move(font)));

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto Sound_Explain = std::make_unique<dae::GameObject>();
	Sound_Explain.get()->SetGameObjectPosition(50, 200);
	Sound_Explain.get()->AddComponent(new dae::TextObject(Sound_Explain.get(), "Press P to play sound", std::move(font)));

	auto P2 = std::make_unique<dae::GameObject>();
	P2.get()->AddComponent(new dae::RenderComponent(P2.get()));
	P2.get()->GetComponent<dae::RenderComponent>()->SetTexture("CharactersSheet.png");
	P2.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 16*0, 16, 16);
	P2.get()->SetGameObjectPosition(16 * 20, 16 * 15);
	P2.get()->AddComponent(new dae::CollisionComponent(P2.get(), 16, 16));
	P2.get()->AddComponent(new HealthComponent(P2.get()));
	P2.get()->AddComponent(new ScoreComponent(P2.get()));
	P2.get()->GetComponent<dae::CollisionComponent>()->AddObserver(new PengoCollisionObserver(P2.get()));
	P2.get()->SetLayer("Player");

	//Borders
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

	auto GameBackground = std::make_unique<dae::GameObject>();
	GameBackground.get()->AddComponent(new dae::RenderComponent(GameBackground.get()));
	GameBackground.get()->GetComponent<dae::RenderComponent>()->SetTexture("LevelsSheet.png");
	GameBackground.get()->GetComponent<dae::RenderComponent>()->SetSourceRect(0, 0, 224, 256);
	GameBackground.get()->SetGameObjectPosition(16 * 0, Config::MENUTOP_SIZE);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 8);
	auto menuBottom = std::make_unique<dae::GameObject>();
	menuBottom.get()->SetGameObjectPosition(Config::BORDER_SIZE, Config::MENUTOP_SIZE + 256.f);
	menuBottom.get()->AddComponent(new dae::TextObject(menuBottom.get(), "ACT 1", std::move(font)));
	
	auto menuUI = std::make_unique<dae::GameObject>();
	menuUI.get()->SetGameObjectPosition(Config::BORDER_SIZE, 0);
	
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto player1_UI = std::make_unique<dae::GameObject>();
	player1_UI.get()->AddComponent(new dae::TextObject(player1_UI.get(), "1P", std::move(font)));
	player1_UI.get()->SetGameObjectPosition(16, 0);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto score_UI = std::make_unique<dae::GameObject>();
	score_UI.get()->AddComponent(new dae::TextObject(score_UI.get(), "0", std::move(font)));
	score_UI.get()->SetGameObjectPosition(100, 0);
	score_UI.get()->SetLayer("Score");

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto highScore_UI = std::make_unique<dae::GameObject>();
	highScore_UI.get()->AddComponent(new dae::TextObject(highScore_UI.get(), "0", std::move(font)));
	highScore_UI.get()->SetGameObjectPosition(150, 0);

	player1_UI.get()->SetParent(menuUI.get(), false);
	score_UI.get()->SetParent(menuUI.get(), false);
	highScore_UI.get()->SetParent(menuUI.get(), false);

	dae::SoundServiceLocator::register_sound_system(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>("Resources/")));
	dae::SoundSystem* ss = &dae::SoundServiceLocator::get_sound_system();
	ss->play("MainBGM.mp3", 5, -1);
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

	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_UP), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(0, -1, 0)));
	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_DOWN), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(0, 1, 0)));
	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_LEFT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(-1, 0, 0)));
	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_DPAD_RIGHT), dae::InputActionType::IsPressed, std::make_unique<dae::Movement>(P2.get(), glm::vec3(1, 0, 0)));

	//dae::InputManager::GetInstance().BindCommand(SDLK_m, dae::InputActionType::IsUp, std::make_unique<dae::SoundMuteCommand>());

	//scene.Add(std::move(backGround));
	//scene.Add(std::move(DAElogo));
	//scene.Add(std::move(text));
	//scene.Add(std::move(P1_Explain));
	//scene.Add(std::move(P2_Explain));
	//scene.Add(std::move(Sound_Explain));

	//dae::Scene* levelScene = dae::SceneManager::GetInstance().CreateScene("levelScene");
	//
	//Level* m_Level1 = new Level( "Resources/Level1.txt" );
	//Level* m_Level2 = new Level("Resources/Level2.txt");
	//
	//std::vector<Level*> levelLayouts{ m_Level1, m_Level2 };
	//
	//std::vector<std::unique_ptr<dae::GameObject>> level1 = m_Level1->LoadLevel();
	//
	//for (auto& object : level1)
	//{
	//	levelScene->Add(std::move(object));
	//}
	//
	//dae::SceneManager::GetInstance().LoadScene("levelScene");

	//dae::InputManager::GetInstance().BindCommand(SDLK_F1, dae::InputActionType::IsUp, std::make_unique<SkipLevel>(nullptr, levelScene, levelLayouts));
	
	Level m_Level{ "Resources/Level1.txt" };
	std::vector<std::unique_ptr<dae::GameObject>> level = m_Level.LoadLevel();





	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_B), dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P1.get(), P1.get()->GetComponent<dae::ScoreComponent>()));
	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_A), dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P1.get(), P1.get()->GetComponent<dae::ScoreComponent>()));
	//dae::InputManager::GetInstance().BindCommand(WORD(XINPUT_GAMEPAD_X), dae::InputActionType::IsDown, std::make_unique<dae::Damage>(P1.get(), P1.get()->GetComponent<dae::HealthComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_z, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P2.get(), P2.get()->GetComponent<dae::ScoreComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_x, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(P2.get(), P2.get()->GetComponent<dae::ScoreComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_c, dae::InputActionType::IsDown, std::make_unique<dae::Damage>(P2.get(), P2.get()->GetComponent<dae::HealthComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_t, dae::InputActionType::IsDown, std::make_unique<dae::Damage>(go.get(), go.get()->GetComponent<dae::HealthComponent>()));
	//dae::InputManager::GetInstance().BindCommand(SDLK_x, dae::InputActionType::IsDown, std::make_unique<dae::PointIncrease>(go.get(), go.get()->GetComponent<dae::ScoreComponent>()));

	//if (g_SteamAchievements)
	//	g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");

	auto gameStatsScene = dae::SceneManager::GetInstance().CreateScene("GameStats");

	auto gameTimer = std::make_unique<dae::GameObject>();
	gameTimer.get()->AddComponent(new TimerComponent(gameTimer.get()));
	gameTimer.get()->SetLayer("Timer");

	auto highScore = std::make_unique<dae::GameObject>();
	highScore.get()->AddComponent(new HighScoreComponent(highScore.get(), "Resources/HighScore.txt", highScore_UI.get()->GetComponent<dae::TextObject>()));
	highScore.get()->SetLayer("HighScore");

	auto score = std::make_unique<dae::GameObject>();
	HighScoreComponent* highScoreComp = highScore.get()->GetComponent<HighScoreComponent>();
	score.get()->AddComponent(new ScoreComponent(score.get(), highScoreComp, score_UI.get()->GetComponent<dae::TextObject>()));
	score.get()->SetLayer("Score");

	gameStatsScene->Add(std::move(gameTimer));
	gameStatsScene->Add(std::move(score));
	gameStatsScene->Add(std::move(highScore));




	auto endScene = dae::SceneManager::GetInstance().CreateScene("EndScene");

	auto backGroundEndScreen = std::make_unique<dae::GameObject>();
	backGroundEndScreen.get()->AddComponent(new dae::RenderComponent(backGroundEndScreen.get()));
	backGroundEndScreen.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	backGroundEndScreen.get()->AddComponent(new dae::TextObject(backGroundEndScreen.get(), "ENDSCREEN", std::move(font)));
	endScene->Add(std::move(backGroundEndScreen));

	auto scoreUI_EndScreen = std::make_unique<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	scoreUI_EndScreen.get()->AddComponent(new dae::TextObject(scoreUI_EndScreen.get(), "0", std::move(font)));
	scoreUI_EndScreen.get()->SetGameObjectPosition(100, 100);
	scoreUI_EndScreen->SetLayer("Score");

	auto highScoreUI_EndScreen = std::make_unique<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	highScoreUI_EndScreen.get()->AddComponent(new dae::TextObject(highScoreUI_EndScreen.get(), "0", std::move(font)));
	highScoreUI_EndScreen->SetLayer("HighScore");

	for (int i = 0; i < 5; i++)
	{
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		auto highScoreUI_Text = std::make_unique<dae::GameObject>();
		highScoreUI_Text.get()->AddComponent(new dae::TextObject(highScoreUI_Text.get(), "0", std::move(font)));
		highScoreUI_Text.get()->SetGameObjectPosition(100, 150.f + (i * 20.f));
		highScoreUI_Text.get()->SetParent(highScoreUI_EndScreen.get(), false);

		endScene->Add(std::move(highScoreUI_Text));
	}

	//highScoreUI_EndScreen.get()->AddComponent(new dae::TextObject(highScoreUI_EndScreen.get(), "0", std::move(font)));
	//highScoreUI_EndScreen.get()->SetGameObjectPosition(100, 200);
	//highScoreUI_EndScreen->SetLayer("HighScore");

	auto EndScreenConfig = std::make_unique<dae::GameObject>();
	EndScreenConfig.get()->AddComponent(new EndScreenComponent(EndScreenConfig.get()));
	EndScreenConfig->SetLayer("Config");

	endScene->Add(std::move(scoreUI_EndScreen));
	endScene->Add(std::move(EndScreenConfig));
	endScene->Add(std::move(highScoreUI_EndScreen));



	scene->Add(std::move(GameBackground));
	//scene.Add(std::move(P2));
	for(auto& object : level)
	{
		scene->Add(std::move(object));
	}
	for (auto& bord : borders)
	{
		scene->Add(std::move(bord));
	}
	scene->Add(std::move(FPS));
	scene->Add(std::move(menuBottom));
	scene->Add(std::move(menuUI));
	scene->Add(std::move(player1_UI));
	scene->Add(std::move(score_UI));
	scene->Add(std::move(highScore_UI));
}
int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}