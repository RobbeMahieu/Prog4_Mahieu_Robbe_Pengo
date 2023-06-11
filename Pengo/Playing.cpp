#include "Playing.h"
#include "LevelLoader.h"
#include "EnemySpawner.h"
#include "Player.h"
#include <InputManager.h>
#include <Keyboard.h>
#include "EndScreen.h"
#include "HealthComponent.h"
#include "DiamondSpawner.h"

using namespace pengo;

Playing::Playing(engine::GameObject* pOwner)
	: GameState(pOwner)
	, m_IsPlaying{ true }
	, m_WonLevel{ true }
	, m_PlayerDied{ false }
	, m_pLevelLoader{ nullptr }
	, m_pEnemySpawner{ nullptr }
	, m_pDiamondSpawner{ nullptr }
	, m_pPlayers{}
	, m_LevelIndex{ 0 }
	, m_pLevel{ nullptr }
	, m_pGame{ nullptr }
{
}

void Playing::OnEnter() {
	
	// Gameobject for the game
	m_pGame = new engine::GameObject();
	m_pGame->AttachTo(m_pOwner, false);

	// Level loading
	m_pLevelLoader = m_pGame->AddComponent<LevelLoader>(32.0f);
	m_pLevelLoader->AddLevelPath("../Data/Levels/level1.dat");
	m_pLevelLoader->AddLevelPath("../Data/Levels/level2.dat");
	m_pLevelLoader->AddLevelPath("../Data/Levels/level3.dat");
	m_pEnemySpawner = m_pGame->AddComponent<EnemySpawner>();
	m_pDiamondSpawner = m_pGame->AddComponent<DiamondSpawner>();

	// Spawn players
	engine::Keyboard* keyboard = engine::InputManager::GetInstance().AddInputDevice<engine::Keyboard>();
	int health{ 3 };
	float movementSpeed{ 100.0f };

	m_pPlayers.push_back(CreatePlayer("pengo.png", keyboard, health, movementSpeed, glm::vec3{ 200, 250, 0 }));

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

	if (m_PlayerDied) {
		RestartLevel();
	}

	// Next Level
	if (m_WonLevel) {
		NextLevel();
	}

	// Game end
	if (!m_IsPlaying) { 
		m_pGame->Destroy();
		return new EndScreen(m_pOwner, m_WonLevel); 
	}

	return nullptr;
}

void Playing::OnNotify(){
	m_WonLevel = true;
}

void Playing::OnNotify(HealthComponent* /*component*/, int health) {
	// Player died
	if (health >= 0) {
		m_PlayerDied = true;
	}
	else {
		m_IsPlaying = false;
		m_WonLevel = false;
	}
}

void Playing::NextLevel() {

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

void Playing::RestartLevel() {
	// Reset player positions
	for (engine::GameObject* player : m_pPlayers)
	{
		player->SetLocalPosition(glm::vec3{ 200, 250, 0 });
	}

	// Set enemies to corners
	std::vector<engine::GameObject*> m_Enemies{ m_pEnemySpawner->GetEnemies() };
	for (int i{ 0 }; i < m_Enemies.size(); ++i) {

		// Refactor to not have hard coded values
		int x =  16 +(i % 2) * 384;
		int y =  16 +(i / 2) * 448;

		m_Enemies[i]->SetLocalPosition(glm::vec3{ x,y,0 });
	}

	m_PlayerDied = false;

}