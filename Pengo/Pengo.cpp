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
#include "InputManager.h"
#include "ScoreComponent.h"
#include "CollisionComponent.h"
#include "SDLSoundSystem.h"
#include "SoundCommands.h"
#include "FpsComponent.h"
#include "EndScreenComponent.h"
#include "Level.h"
#include "GameConfig.h"
#include "LoggingSoundSystem.h"
#include "TimerComponent.h"
#include "HighScoreComponent.h"
#include "GameCommands.h"

void load()
{
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_1, dae::InputActionType::IsUp, std::make_unique<StartGameCommand>(GameModes::Single));
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_2, dae::InputActionType::IsUp, std::make_unique<StartGameCommand>(GameModes::CoOp));
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_3, dae::InputActionType::IsUp, std::make_unique<StartGameCommand>(GameModes::Versus));

	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_M, dae::InputActionType::IsUp, std::make_unique<SoundMuteCommand>());

	dae::SoundServiceLocator::register_sound_system(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>("Resources/")));
	dae::SoundServiceLocator::get_sound_system()->play("MainBGM.mp3", 5, -1);


	//Start Screen
	auto startScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	
	auto backGroundStartScreen = std::make_unique<dae::GameObject>();
	backGroundStartScreen.get()->AddComponent(new dae::RenderComponent(backGroundStartScreen.get()));
	backGroundStartScreen.get()->GetComponent<dae::RenderComponent>()->SetTexture("background.tga");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	backGroundStartScreen.get()->AddComponent(new dae::TextObject(backGroundStartScreen.get(), "STARTSCREEN", std::move(font)));

	dae::SceneManager::GetInstance().LoadScene("StartScreen");



	//Game UI
	auto scene = dae::SceneManager::GetInstance().CreateScene("GameLayout");

	//FPS
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto FPS = std::make_unique<dae::GameObject>();
	FPS.get()->SetGameObjectPosition(100, 16);
	FPS.get()->AddComponent(new dae::TextObject(FPS.get(), "0FPS", std::move(font)));
	FPS.get()->AddComponent(new FpsComponent(FPS.get(), FPS.get()->GetComponent<dae::TextObject>()));

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


	//Game Level
	dae::Scene* levelScene = dae::SceneManager::GetInstance().CreateScene("LevelScene");
	std::vector<std::unique_ptr<Level>> levelLayouts;

	levelLayouts.emplace_back(std::make_unique<Level>("Resources/Level1.txt"));
	levelLayouts.emplace_back(std::make_unique<Level>("Resources/Level2.txt"));
	levelLayouts.emplace_back(std::make_unique<Level>("Resources/Level3.txt"));
	levelLayouts.emplace_back(std::make_unique<Level>("Resources/Level4.txt"));
	levelLayouts.emplace_back(std::make_unique<Level>("Resources/Level5.txt"));

	std::vector<std::unique_ptr<dae::GameObject>> level = levelLayouts.at(0)->LoadLevel();

	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F1, dae::InputActionType::IsUp, std::make_unique<NextLevel>(levelScene, std::move(levelLayouts)));

	for(auto& object : level)
	{
		levelScene->Add(std::move(object));
	}


	//Game Stats
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



	//End Scene
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

	auto EndScreenConfig = std::make_unique<dae::GameObject>();
	EndScreenConfig.get()->AddComponent(new EndScreenComponent(EndScreenConfig.get()));
	EndScreenConfig->SetLayer("Config");



	startScene->Add(std::move(backGroundStartScreen));

	scene->Add(std::move(GameBackground));

	scene->Add(std::move(FPS));
	scene->Add(std::move(menuBottom));
	scene->Add(std::move(menuUI));
	scene->Add(std::move(player1_UI));
	scene->Add(std::move(score_UI));
	scene->Add(std::move(highScore_UI));

	gameStatsScene->Add(std::move(gameTimer));
	gameStatsScene->Add(std::move(score));
	gameStatsScene->Add(std::move(highScore));

	endScene->Add(std::move(scoreUI_EndScreen));
	endScene->Add(std::move(EndScreenConfig));
	endScene->Add(std::move(highScoreUI_EndScreen));

}
int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}