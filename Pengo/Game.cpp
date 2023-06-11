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
	engine::InputManager::GetInstance().AddInputDevice<engine::Keyboard>();
	engine::InputManager::GetInstance().AddInputDevice<engine::XBoxController>(0);
	engine::InputManager::GetInstance().AddInputDevice<engine::XBoxController>(1);

	auto& scene = engine::SceneManager::GetInstance().CreateScene("Pengo");

	// Game Manager
	engine::GameObject* gameManager{ new engine::GameObject() };
	gameManager->AddComponent<GameManager>();
	scene.Add(gameManager);
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
// - Versus
// - Sprites + animations if time
// - Sound
// - Named scores
// - Clean up + asserts
// - Refactor enemy, ice, points
//
