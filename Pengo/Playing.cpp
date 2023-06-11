#include "Playing.h"
#include "LevelLoader.h"
#include "EnemySpawner.h"
#include "Player.h"
#include "Block.h"
#include <InputManager.h>
#include <InputDevice.h>
#include <XBoxController.h>
#include <Keyboard.h>
#include "EndScreen.h"
#include "HealthComponent.h"
#include "DiamondSpawner.h"
#include "PointManager.h"
#include "PointsHUD.h"
#include "ResourceManager.h"

using namespace pengo;

Playing::Playing(engine::GameObject* pOwner, GameMode mode)
	: GameState(pOwner)
	, m_IsPlaying{ true }
	, m_WonLevel{ true }
	, m_pLevelLoader{ nullptr }
	, m_pEnemySpawner{ nullptr }
	, m_pDiamondSpawner{ nullptr }
	, m_pPlayers{}
	, m_LevelIndex{ 0 }
	, m_pLevel{ nullptr }
	, m_pGame{ nullptr }
	, m_pRoot{ nullptr }
	, m_pHUD{ nullptr }
	, m_GameMode{ mode }
	, m_LevelStartTime{}
{
}

void Playing::OnLeave() {
	m_pRoot->Destroy();
}

void Playing::OnEnter() {
	
	m_pRoot = new engine::GameObject();
	m_pRoot->AttachTo(m_pOwner, false);

	// Gameobject for the game
	m_pGame = new engine::GameObject();
	m_pGame->AttachTo(m_pRoot, false);
	m_pGame->SetLocalPosition(0, 32);

	// Level loading
	m_pLevelLoader = m_pGame->AddComponent<LevelLoader>(32.0f);
	m_pLevelLoader->AddLevelPath("../Data/Levels/level1.dat");
	m_pLevelLoader->AddLevelPath("../Data/Levels/level2.dat");
	m_pLevelLoader->AddLevelPath("../Data/Levels/level3.dat");
	m_pEnemySpawner = m_pGame->AddComponent<EnemySpawner>();
	m_pDiamondSpawner = m_pGame->AddComponent<DiamondSpawner>();

	// Spawn players
	AddPlayers();

	// Add walls
	engine::GameObject* walls{ CreateWalls(16, 448, 512) };
	walls->AttachTo(m_pGame, false);

	// HUD
	AddHUD();

	for (engine::GameObject* player : m_pPlayers)
	{
		player->AttachTo(m_pOwner, false);
	}

	// Events
	m_pEnemySpawner->m_EnemiesKilled.AddObserver(this);
	for (engine::GameObject* player : m_pPlayers)
	{
		player->GetComponent<HealthComponent>()->HealthChanged.AddObserver(this);
	}
}

GameState* Playing::Update() {

	// Next Level
	if (m_WonLevel) {
		NextLevel();
	}

	// Game end
	if (!m_IsPlaying || m_pPlayers.size() == 0) {
		return new EndScreen(m_pOwner, m_WonLevel, m_GameMode); 
	}

	return nullptr;
}

void Playing::OnNotify(){
	m_WonLevel = true;

	CalculateBonus();
}

void Playing::OnNotify(HealthComponent* component, int health) {
	// Player died
	component->GetOwner()->SetLocalPosition(glm::vec3{ 200, 250, 0 });
	
	// Player has no more lives
	if (health < 0) {
		m_pPlayers.erase(std::remove(m_pPlayers.begin(), m_pPlayers.end(), component->GetOwner()), m_pPlayers.end());
	}
	
}

void Playing::NextLevel() {

	m_LevelStartTime = std::chrono::high_resolution_clock::now();

	// Check if there is a next level
	if (m_LevelIndex >= m_pLevelLoader->GetLevelAmount()) {
		m_IsPlaying = false;
		return;
	}

	m_WonLevel = false;

	// Clear everything in the level
	if (m_pLevel) {
		m_pLevel->Destroy();
	}

	// Spawn blocks
	m_pLevel = m_pLevelLoader->LoadLevel(m_LevelIndex);
	m_pLevel->AttachTo(m_pGame, false);

	// Spawn enemies
	m_pEnemySpawner->PickEnemyLocations(m_pLevel->GetChildren(), 6);

	// Spawn diamonds
	m_pDiamondSpawner->PickDiamondLocations(m_pLevel->GetChildren(), 3);

	// Increase LevelIndex
	++m_LevelIndex;
}

void Playing::AddPlayers() {

	int health{ 3 };
	float movementSpeed{ 100.0f };

	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	engine::Keyboard* keyboard{ dynamic_cast<engine::Keyboard*>(devices[0]) };
	engine::XBoxController* controller1{ dynamic_cast<engine::XBoxController*>(devices[1]) };
	engine::XBoxController* controller2{ dynamic_cast<engine::XBoxController*>(devices[2]) };
	assert(keyboard && controller1 && controller2 && "Device was not correct!");

	switch (m_GameMode) {
		case GameMode::Single:
		{
			engine::GameObject* player{ CreatePlayer("Sprites/pengo.png", keyboard, controller1, health, movementSpeed) };
			player->SetLocalPosition(192, 224);
			player->AttachTo(m_pGame, false);
			m_pPlayers.push_back(player);
			break;
		}

		case GameMode::Coop:
		{
			engine::GameObject* player{ CreatePlayer("Sprites/pengo.png", keyboard, controller2, health, movementSpeed) };
			player->SetLocalPosition(128, 224);
			player->AttachTo(m_pGame, false);
			m_pPlayers.push_back(player);

			engine::GameObject* player2{ CreatePlayer("Sprites/pengoAlt.png", nullptr, controller1, health, movementSpeed) };
			player2->SetLocalPosition(256, 224);
			player2->AttachTo(m_pGame, false);
			m_pPlayers.push_back(player2);

			break;
		}

		case GameMode::Versus:
			engine::GameObject* player{ CreatePlayer("Sprites/pengo.png", keyboard, controller2, health, movementSpeed) };
			player->SetLocalPosition(128, 224);
			player->AttachTo(m_pGame, false);
			m_pPlayers.push_back(player);

			// Create controllable enemy
			engine::GameObject* player2{ CreateControllableSnowBee("Sprites/pengo.png", nullptr, controller1)};
			player2->SetLocalPosition(128, 224);
			player2->AttachTo(m_pGame, false);
			m_pPlayers.push_back(player);

			break;
	}
}

void Playing::CalculateBonus() {
	auto currentTime{ std::chrono::high_resolution_clock::now() };
	float seconds{ std::chrono::duration<float>(currentTime - m_LevelStartTime).count() };

	if (seconds < 60.0f) {
		PointManager::GetInstance().AddScore(int(60.0f - seconds) * 100);
	}
}

void Playing::AddHUD() {

	m_pHUD = new engine::GameObject();
	m_pHUD->AttachTo(m_pRoot, true);

	// Plater HUDs
	for (int i{ 0 }; i < m_pPlayers.size(); ++i) {
		engine::GameObject* playerHUD = CreatePlayerHUD(m_pPlayers[i], "Sprites/smallPengo.png", i + 1);
		playerHUD->AttachTo(m_pHUD, false);
		playerHUD->SetLocalPosition(5 + 360.0f*i, 3);
	}

	// Score HUD
	engine::GameObject* scoreHUD{ new engine::GameObject() };
	auto textFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 20);
	scoreHUD->AddComponent<engine::TextRenderComponent>(" ", textFont);
	scoreHUD->AddComponent<PointsHUD>();
	scoreHUD->SetLocalPosition(150, 3);
	scoreHUD->AttachTo(m_pHUD, false);
}