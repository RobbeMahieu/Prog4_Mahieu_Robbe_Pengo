#include "Playing.h"
#include "LevelLoader.h"
#include "EnemySpawner.h"
#include "Player.h"
#include <InputManager.h>
#include <Keyboard.h>

using namespace pengo;

Playing::Playing(engine::GameObject* pOwner)
	: GameState(pOwner)
	, m_IsPlaying{ true }
	, m_pLevelLoader{ nullptr }
	, m_pEnemySpawner{ nullptr }
	, m_pPlayers{}
{
}

void Playing::OnEnter() {
	
	// Gameobject for the game
	m_pGame = new engine::GameObject();
	m_pGame->AttachTo(m_pOwner, false);

	// Set up level
	m_pLevelLoader = m_pGame->AddComponent<LevelLoader>(32.0f);
	m_pLevelLoader->AddLevelPath("../Data/Levels/level1.dat");
	engine::GameObject* level = m_pLevelLoader->LoadLevel(0);
	level->AttachTo(m_pGame, false);

	// Choose enemy spawn locations
	m_pEnemySpawner = m_pGame->AddComponent<EnemySpawner>();
	m_pEnemySpawner->PickEnemyLocations(level->GetChildren(), 6);

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

	// Game end
	if (!m_IsPlaying) { 

		m_pGame->Destroy();

		return nullptr; 
	}

	return nullptr;
}

void Playing::OnNotify(){
	m_IsPlaying = false;
}