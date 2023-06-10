#include "Player.h"
#include "TextureRenderComponent.h"
#include "PlayerMovement.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "PointsHUD.h"
#include "HealthHUD.h"
#include "PushComponent.h"

using namespace pengo;

engine::GameObject* pengo::CreatePlayer(std::string spritePath, engine::Keyboard* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new engine::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<engine::TextureRenderComponent>(spritePath);
	player->AddComponent<PlayerMovement>(movementSpeed, pDevice);
	player->AddComponent<CollisionComponent>(32.0f, 32.0f, false, PhysicsType::DYNAMIC);
	player->AddComponent<HealthComponent>(health);
	player->AddComponent<PointComponent>();
	player->AddComponent<PushComponent>(pDevice);

	return player;
}

engine::GameObject* pengo::CreatePlayer(std::string spritePath, engine::XBoxController* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new engine::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<engine::TextureRenderComponent>(spritePath);
	player->AddComponent<PlayerMovement>(movementSpeed, pDevice);
	player->AddComponent<CollisionComponent>(32.0f, 32.0f, false, PhysicsType::DYNAMIC);
	player->AddComponent<HealthComponent>(health);
	player->AddComponent<PointComponent>();
	player->AddComponent<PushComponent>(pDevice);

	return player;
}

engine::GameObject* pengo::CreatePlayerHUD(engine::GameObject* pPlayer, glm::vec3 position) {
	auto playerHUD = new engine::GameObject();
	playerHUD->SetLocalPosition(position);

	auto textFont = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	HealthComponent* pPlayerHealth = pPlayer->GetComponent<HealthComponent>();
	PointComponent* pPlayerPoints = pPlayer->GetComponent<PointComponent>();

	if (pPlayerHealth) {
		auto playerHealthHUD = new engine::GameObject();
		playerHealthHUD->AddComponent<engine::TextRenderComponent>("lives", textFont);
		playerHealthHUD->AddComponent<HealthHUD>(pPlayerHealth);
		playerHealthHUD->AttachTo(playerHUD, false);
	}

	if (pPlayerPoints) {
		auto playerPointsHUD = new engine::GameObject();
		playerPointsHUD->AddComponent<engine::TextRenderComponent>("points", textFont);
		playerPointsHUD->AddComponent<PointsHUD>(pPlayerPoints);
		playerPointsHUD->AttachTo(playerHUD, false);
		playerPointsHUD->SetLocalPosition(0, 20);
	}

	return playerHUD;
}