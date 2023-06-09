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
#include "Player.h"
#include "Block.h"
#include "LevelLoader.h"

using namespace pengo;

void load()
{
	// Add input devices
	// (I'd like to do this automatically in the future)
	engine::XBoxController* controller0 = engine::InputManager::GetInstance().AddInputDevice<engine::XBoxController>(0);
	engine::Keyboard* keyboard = engine::InputManager::GetInstance().AddInputDevice<engine::Keyboard>();

	auto& scene = engine::SceneManager::GetInstance().CreateScene("Pengo");

	// Remove testing (delete this in the end!)
	auto parent = new engine::GameObject();
	scene.Add(parent);

	auto object = new engine::GameObject();
	object->AddComponent<engine::TextureRenderComponent>("background.tga");
	object->AddComponent<FPSComponent>();
	object->RemoveComponent<FPSComponent>();
	object->AttachTo(parent, true);

	auto object2 = new engine::GameObject();
	object2->AddComponent<engine::TextureRenderComponent>("background.tga");
	object2->AttachTo(parent, true);
	scene.Add(object2);
	object2->AttachTo(nullptr, false);

	scene.Remove(parent);

	// Background
	auto background = new engine::GameObject();
	background->SetLocalPosition(0, 0);
	background->AddComponent<engine::TextureRenderComponent>("controls.png");
	scene.Add(background);

	int health{ 5 };
	float movementSpeed{ 100.0f };

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

	// Level
	engine::GameObject* gameManager{ new engine::GameObject() };
	LevelLoader* levelLoader = gameManager->AddComponent<LevelLoader>(32.0f);
	levelLoader->AddLevelPath("../Data/Levels/level1.dat");

	scene.Add(gameManager);
	scene.Add(levelLoader->LoadLevel(0));

	// Player 1
	auto player1 = CreatePlayer("pengo.png", keyboard, health, movementSpeed);
	player1->SetLocalPosition(200, 250);
	scene.Add(player1);

	// Player 2
	auto player2 = CreatePlayer("snowbee.png", controller0, health, movementSpeed * 2);
	player2->SetLocalPosition(100, 250);
	scene.Add(player2);

	// HUD
	/*auto player1HUD = CreatePlayerHUD(player1, glm::vec3{0,200,0});
	scene.Add(player1HUD);

	auto player2HUD = CreatePlayerHUD(player2, glm::vec3{ 0,300,0 });
	scene.Add(player2HUD);*/

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
// Think about command ownership (high priority)
// Look into prototype (low priority)
// Refactor collision componeten to use the check collision function (return struct with info about collision)
// Add own struct for rect
// 
// Gameplay related:
// - Grid (No need right now?)
// - Enemies
// - Level generation
// - Multiplayer
// - Diamond bonus
// - Egg spawning
// - Sprites
//
