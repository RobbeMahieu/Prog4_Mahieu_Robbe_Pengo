#include "Player.h"
#include "TextureRenderComponent.h"
#include "PlayerMovement.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "PointsHUD.h"
#include "HealthHUD.h"
#include "PushComponent.h"
#include "KillPlayerComponent.h"

using namespace pengo;

engine::GameObject* pengo::CreatePlayer(std::string spritePath, engine::Keyboard* keyboard, engine::XBoxController* controller, int health, float movementSpeed, glm::vec3 position) {

	auto player = new engine::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<engine::TextureRenderComponent>(spritePath);

	if (keyboard) {
		player->AddComponent<PlayerMovement>(movementSpeed, keyboard);
		player->AddComponent<PushComponent>(keyboard);
	}

	if (controller) {
		player->AddComponent<PlayerMovement>(movementSpeed, controller);
		player->AddComponent<PushComponent>(controller);
	}

	player->AddComponent<CollisionComponent>(32.0f, 32.0f, false, CollisionLayer::PLAYER);
	player->AddComponent<HealthComponent>(health);


	return player;
}

engine::GameObject* pengo::CreateControllableSnowBee(std::string spritePath, engine::Keyboard* keyboard, engine::XBoxController* controller, glm::vec3 position) {
	auto bee = new engine::GameObject();
	bee->SetLocalPosition(position);
	bee->AddComponent<engine::TextureRenderComponent>("Sprites/snowbee.png");
	bee->AddComponent<CollisionComponent>(32.0f, 32.0f, false, CollisionLayer::ENEMY);
	
	if (keyboard) {
		bee->AddComponent<PlayerMovement>(50.0f, keyboard);
	}

	if (controller) {
		bee->AddComponent<PlayerMovement>(50.0f, controller);
	}

	bee->AddComponent<KillPlayerComponent>();

	return bee;
}


engine::GameObject* pengo::CreatePlayerHUD(engine::GameObject* pPlayer, glm::vec3 position) {
	auto playerHUD = new engine::GameObject();
	playerHUD->SetLocalPosition(position);

	auto textFont = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	HealthComponent* pPlayerHealth = pPlayer->GetComponent<HealthComponent>();
	//PointComponent* pPlayerPoints = pPlayer->GetComponent<PointComponent>();

	if (pPlayerHealth) {
		auto playerHealthHUD = new engine::GameObject();
		playerHealthHUD->AddComponent<engine::TextRenderComponent>("lives", textFont);
		playerHealthHUD->AddComponent<HealthHUD>(pPlayerHealth);
		playerHealthHUD->AttachTo(playerHUD, false);
	}

	/*if (pPlayerPoints) {
		auto playerPointsHUD = new engine::GameObject();
		playerPointsHUD->AddComponent<engine::TextRenderComponent>("points", textFont);
		playerPointsHUD->AddComponent<PointsHUD>(pPlayerPoints);
		playerPointsHUD->AttachTo(playerHUD, false);
		playerPointsHUD->SetLocalPosition(0, 20);
	}*/

	return playerHUD;
}