#include "Player.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
#include "BasicMovement.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "XBoxController.h"
#include "ResourceManager.h"
#include "TextRenderComponent.h"
#include "PointsHUD.h"
#include "HealthHUD.h"
#include "PushComponent.h"

dae::GameObject* CreatePlayer(std::string spritePath, Keyboard* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new dae::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<TextureRenderComponent>(spritePath);
	player->AddComponent<BasicMovement>(movementSpeed, pDevice);
	player->AddComponent<CollisionComponent>(32, 32, false, PhysicsType::DYNAMIC);
	player->AddComponent<PushComponent>(pDevice);
	player->AddComponent<HealthComponent>(health);
	player->AddComponent<PointComponent>();

	return player;
}

dae::GameObject* CreatePlayer(std::string spritePath, XBoxController* pDevice, int health, float movementSpeed, glm::vec3 position) {

	auto player = new dae::GameObject();
	player->SetLocalPosition(position);
	player->AddComponent<TextureRenderComponent>(spritePath);
	player->AddComponent<BasicMovement>(movementSpeed, pDevice);
	player->AddComponent<CollisionComponent>(32, 32, false, PhysicsType::DYNAMIC);
	player->AddComponent<PushComponent>(pDevice);
	player->AddComponent<HealthComponent>(health);
	player->AddComponent<PointComponent>();

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