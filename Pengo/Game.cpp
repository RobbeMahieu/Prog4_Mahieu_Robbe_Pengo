#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextRenderComponent.h"
#include "TextureRenderComponent.h"
#include "FPSComponent.h"
#include "XBoxController.h"
#include "Keyboard.h"
#include <SDL.h>
#include "Block.h"
#include "GameManager.h"

using namespace pengo;

void load()
{
	// Add input devices
	// (I'd like to do this automatically in the future)
	//engine::XBoxController* controller0 = engine::InputManager::GetInstance().AddInputDevice<engine::XBoxController>(0);


	auto& scene = engine::SceneManager::GetInstance().CreateScene("Pengo");

	// Background
	auto background = new engine::GameObject();
	background->SetLocalPosition(0, 0);
	background->AddComponent<engine::TextureRenderComponent>("controls.png");
	scene.Add(background);

	// Walls
	int wallSize = 16;
	int widthSize = 448 / wallSize;
	int heightSize = 512 / wallSize;

	// Top Bottom
	for (int i{ 0 }; i < widthSize; ++i) {

		// Top
		auto wallTop = CreateWallBlock(glm::vec3{ i * wallSize, 0, 0 });
		scene.Add(wallTop);

		// Bottom
		auto wallBottom = CreateWallBlock(glm::vec3{ i * wallSize, (heightSize - 1) * wallSize, 0 });
		scene.Add(wallBottom);

	}

	for (int i{ 0 }; i < heightSize; ++i) {
		// Left
		auto wallLeft = CreateWallBlock(glm::vec3{ 0, i * wallSize, 0 });
		scene.Add(wallLeft);

		// Right
		auto wallRight = CreateWallBlock(glm::vec3{ (widthSize - 1) * wallSize, i * wallSize, 0 });
		scene.Add(wallRight);
	}

	// Game Manager
	engine::GameObject* gameManager{ new engine::GameObject() };
	gameManager->AddComponent<GameManager>();
	scene.Add(gameManager);

	// FPS counter
	auto FPSCounter = new engine::GameObject();
	auto TitleFont = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textFont = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	FPSCounter->AddComponent<engine::TextRenderComponent>("test", TitleFont);
	FPSCounter->AddComponent<FPSComponent>();
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);

}

int main(int, char* []) {
	engine::Minigin gameEngine("../Data/");
	gameEngine.Run(load);
	return 0;
}

// Todo:
// Commands with parameters (low priority)
// Look into prototype (low priority)
// Add own struct for rect
// 
// Gameplay related:
// - Multiplayer
// - Diamond bonus
// - Game loop
// - Sprites
// - Sound
// - Menu
//
