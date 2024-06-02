#include <stdexcept>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Minigin.h"

#include <chrono>
#include <thread>
#include <vector>
#include <steam_api.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <iostream>
#include <memory>
#include <Xinput.h>

#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "SoundServiceLocator.h"
#define MS_PER_FRAME(fps) (1000.0f / (fps))
#define FPS 120
SDL_Window* g_window{};


void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_MIXER_VERSION(&version)
		printf("We compiled against SDL_mixer version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);
	
	version = *Mix_Linked_Version();
	printf("We are linking against SDL_mixer version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		224,
		296,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	//VSYNC
	//SDL_RenderSetVSync(Renderer::GetInstance().GetSDLRenderer(), true);

	#if NDEBUG
	SoundServiceLocator::register_sound_system(std::make_unique<SDLSoundSystem>(dataPath));
	#else
	dae::SoundServiceLocator::register_sound_system(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>(dataPath)));
	#endif

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	const float fixedTimeStep = 1.0f / FPS;

	constexpr auto targetFrameTime = std::chrono::milliseconds(static_cast<long long>(MS_PER_FRAME(FPS)));

	std::thread soundThread([&]() {
		while (doContinue) {
			SoundServiceLocator::get_sound_system().Update();
		}
	});

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;

		sceneManager.CollisionDetection();

		doContinue = input.ProcessInput(deltaTime);

		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		sceneManager.Update(deltaTime);


		//SoundServiceLocator::get_sound_system().Update();


		sceneManager.LateUpdate(deltaTime);
		renderer.Render();

		//SteamAPI_RunCallbacks();
		// Calculate the sleep time until the next frame
		const auto sleepTime = currentTime + targetFrameTime - std::chrono::high_resolution_clock::now();
		
		std::this_thread::sleep_for(sleepTime);
	}

	SoundServiceLocator::get_sound_system().Stop();
	soundThread.join();
}
