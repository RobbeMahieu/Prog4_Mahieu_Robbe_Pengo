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
#include "StickyComponent.h"
#include "Stunnable.h"

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
	bee->AddComponent<engine::TextureRenderComponent>("Sprites/snowbeeAlt.png");
	bee->AddComponent<CollisionComponent>(32.0f, 32.0f, false, CollisionLayer::ENEMY);
	
	if (keyboard) {
		bee->AddComponent<PlayerMovement>(50.0f, keyboard);
	}

	if (controller) {
		bee->AddComponent<PlayerMovement>(50.0f, controller);
	}

	bee->AddComponent<StickyComponent>();
	bee->AddComponent<KillPlayerComponent>();
	bee->AddComponent<Stunnable>();

	return bee;
}


engine::GameObject* pengo::CreatePlayerHUD(engine::GameObject* pPlayer, std::string iconPath, int index, glm::vec3 position) {
	auto playerHUD = new engine::GameObject();
	playerHUD->SetLocalPosition(position);

	const auto textFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 10);

	// Player index
	const std::string name{ "PLAYER " + std::to_string(index) };
	playerHUD->AddComponent<engine::TextRenderComponent>(name, textFont);

	// Health hud
	HealthComponent* pPlayerHealth = pPlayer->GetComponent<HealthComponent>();
	auto playerHealthHUD = new engine::GameObject();
	playerHealthHUD->AddComponent<HealthHUD>(pPlayerHealth, iconPath);
	playerHealthHUD->AttachTo(playerHUD, false);
	playerHealthHUD->SetLocalPosition(0, 12);

	return playerHUD;
}