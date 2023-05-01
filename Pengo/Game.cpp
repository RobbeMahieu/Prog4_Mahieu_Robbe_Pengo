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
#include "HealthComponent.h"
#include "HealthHUD.h"
#include "PointComponent.h"
#include "PointsHUD.h"
#include "BasicMovement.h"
#include "FPSComponent.h"
#include "XBoxController.h"
#include "Keyboard.h"
#include <SDL.h>

// Create GameObject functions
dae::GameObject* CreatePlayer(std::string spritePath, Keyboard* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
dae::GameObject* CreatePlayer(std::string spritePath, XBoxController* keyboard, int health = 5, float movementSpeed = 100.0f, glm::vec3 position = glm::vec3{ 0,0,0 });
dae::GameObject* CreatePlayerHUD(dae::GameObject* player, glm::vec3 position = glm::vec3{ 0,0,0 });

void load()
{
	// Add input devices
	// (I'd like to do this automatically in the future)
	XBoxController* controller0 = dae::InputManager::GetInstance().AddInputDevice<XBoxController>(0);
	Keyboard* keyboard = dae::InputManager::GetInstance().AddInputDevice<Keyboard>();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Remove testing
	auto parent = new dae::GameObject();
	scene.Add(parent);

	auto object = new dae::GameObject();
	object->AddComponent<TextureRenderComponent>("background.tga");
	object->AddComponent<FPSComponent>();
	object->RemoveComponent<FPSComponent>();
	object->AttachTo(parent, true);

	auto object2 = new dae::GameObject();
	object2->AddComponent<TextureRenderComponent>("background.tga");
	object2->AttachTo(parent, true);
	scene.Add(object2);
	object2->AttachTo(nullptr, false);

	scene.Remove(parent);

	// Background
	auto background = new dae::GameObject();
	background->SetLocalPosition(0, 0);
	background->AddComponent<TextureRenderComponent>("controls.png");
	scene.Add(background);

	// FPS counter
	auto FPSCounter = new dae::GameObject();
	auto TitleFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	FPSCounter->AddComponent<TextRenderComponent>("test", TitleFont);
	FPSCounter->AddComponent<FPSComponent>();
	FPSCounter->SetLocalPosition(0, 0);
	scene.Add(FPSCounter);

	int health{ 5 };
	float movementSpeed{ 100.0f };

	// Player 1
	auto player1 = CreatePlayer("pengo.png", keyboard, health, movementSpeed);
	scene.Add(player1);

	// Player 2
	auto player2 = CreatePlayer("snowbee.png", controller0, health, movementSpeed * 2);
	scene.Add(player2);

	// HUD
	auto player1HUD = CreatePlayerHUD(player1, glm::vec3{ 0,200,0 });
	scene.Add(player1HUD);

	auto player2HUD = CreatePlayerHUD(player2, glm::vec3{ 0,300,0 });
	scene.Add(player2HUD);

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}

dae::GameObject* CreatePlayer(std::string spritePath, Keyboard* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new dae::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<TextureRenderComponent>(spritePath);
	player->AddComponent<BasicMovement>(movementSpeed, pDevice);
	auto pPlayerHealth = player->AddComponent<HealthComponent>(health);
	auto pPlayerPoints = player->AddComponent<PointComponent>();

	// Test key bindings
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&HealthComponent::TakeDamage, pPlayerHealth, 1)), pDevice->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_RETURN, new Command(std::bind(&PointComponent::AddScore, pPlayerPoints, 50)), pDevice->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_RSHIFT, new Command(std::bind(&PointComponent::AddScore, pPlayerPoints, 100)), pDevice->GetID(), KeyState::OnPress);

	return player;
}

dae::GameObject* CreatePlayer(std::string spritePath, XBoxController* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new dae::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<TextureRenderComponent>(spritePath);
	player->AddComponent<BasicMovement>(movementSpeed, pDevice);
	auto pPlayerHealth = player->AddComponent<HealthComponent>(health);
	auto pPlayerPoints = player->AddComponent<PointComponent>();

	// Test key bindings
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_X, new Command(std::bind(&HealthComponent::TakeDamage, pPlayerHealth, 1)), pDevice->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PointComponent::AddScore, pPlayerPoints, 50)), pDevice->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_B, new Command(std::bind(&PointComponent::AddScore, pPlayerPoints, 100)), pDevice->GetID(), KeyState::OnPress);

	return player;
}

dae::GameObject* CreatePlayerHUD(dae::GameObject* pPlayer, glm::vec3 position) {
	auto playerHUD = new dae::GameObject();
	playerHUD->SetLocalPosition(position);

	auto textFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	HealthComponent* pPlayerHealth = pPlayer->GetComponent<HealthComponent>();
	PointComponent* pPlayerPoints = pPlayer->GetComponent<PointComponent>();

	if (pPlayerHealth) {
		auto playerHealthHUD = new dae::GameObject();
		playerHealthHUD->AddComponent<TextRenderComponent>("lives", textFont);
		playerHealthHUD->AddComponent<HealthHUD>(pPlayerHealth);
		playerHealthHUD->AttachTo(playerHUD, false);
	}

	if (pPlayerPoints) {
		auto playerPointsHUD = new dae::GameObject();
		playerPointsHUD->AddComponent<TextRenderComponent>("points", textFont);
		playerPointsHUD->AddComponent<PointsHUD>(pPlayerPoints);
		playerPointsHUD->AttachTo(playerHUD, false);
		playerPointsHUD->SetLocalPosition(0, 20);
	}

	return playerHUD;
}

// Questions:
// - Namespaces: engine needs one, does the game need one too?
// - Scalability of subjects/events
// - Creation of game object => all in load now, is there a better way?
//