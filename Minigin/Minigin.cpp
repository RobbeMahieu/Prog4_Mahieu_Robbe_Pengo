#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameServiceLocator.h"
#include "SDL_SoundSystem.h"
#include "LoggingSoundSystem.h"
#include "GameTime.h"
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>

using namespace engine;

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
}

Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		448,
		512,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	SDL_Quit();
}

void Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& gameTime = GameTime::GetInstance();

#if _DEBUG
	GameServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SDL_SoundSystem>()));
#else
	GameServiceLocator::RegisterSoundSystem(std::make_unique<SDL_SoundSystem>());
#endif

	gameTime.Init();

	bool doContinue = true;
	const float fixedTimeStepSec{ gameTime.GetFixedUpdateStep() };
	const float desiredFPS{ 60.0f };
	const int frameTimeMs{ int(1000 / desiredFPS) };
	float lag = 0.0f;

	while (doContinue)
	{
		gameTime.Update();
		lag += gameTime.GetElapsedSec();

		// Process input
		doContinue = input.ProcessInput();

		// Fixed Update
		while (lag >= fixedTimeStepSec) {
			sceneManager.FixedUpdate();
			lag -= fixedTimeStepSec;
		}

		// Normal Update
		sceneManager.Update();

		// Renders
		renderer.Render();

		// Sleep for rest of frame
		const auto sleepTime = gameTime.GetFrameStartTime() + std::chrono::milliseconds(frameTimeMs) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}
