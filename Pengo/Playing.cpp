#include "Playing.h"
#include "LevelLoader.h"
#include "EnemySpawner.h"
#include "Player.h"
#include <InputManager.h>
#include <Keyboard.h>
#include "EndScreen.h"

using namespace pengo;

Playing::Playing(engine::GameObject* pOwner)
	: GameState(pOwner)
	, m_IsPlaying{ true }
	, m_WonLevel{ true }
	, m_pLevelLoader{ nullptr }
	, m_pEnemySpawner{ nullptr }
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

	// Spawn players
	engine::Keyboard* keyboard = engine::InputManager::GetInstance().AddInputDevice<engine::Keyboard>();
	int health{ 5 };
	float movementSpeed{ 100.0f };

	m_pPlayers.push_back(CreatePlayer("pengo.png", keyboard, health, movementSpeed, glm::vec3{ 200, 250, 0 }));

	for (engine::GameObject* player : m_pPlayers)
	{
		player->AttachTo(m_pOwner, false);
	}

	// Events
	m_pEnemySpawner->m_EnemiesKilled.AddObserver(this);

}

GameState* Playing::Update() {

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
	m_pEnemySpawner->PickEnemyLocations(m_pLevel->GetChildren(), 1);

	// Increase LevelIndex
	++m_LevelIndex;
}