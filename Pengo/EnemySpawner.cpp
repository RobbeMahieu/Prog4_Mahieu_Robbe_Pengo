#include "EnemySpawner.h"
#include "SnowBee.h"
#include "StickyComponent.h"
#include "Stunnable.h"
#include "SlidingComponent.h"
#include "PointManager.h"
#include "GameServiceLocator.h"

using namespace pengo;

EnemySpawner::EnemySpawner(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_RandomEngine{ std::random_device{}() }
	, m_EnemyCounter{ 0 }
	, m_EnemiesKilled{}
	, m_MaxActiveEnemies{ 3 }
{
}

void EnemySpawner::Update() {
	if (m_ActiveEnemies.size() < m_MaxActiveEnemies) {
		SpawnEnemy();
	}

	if (m_ActiveEnemies.size() == 0) {
		m_EnemiesKilled.Broadcast();
	}
}

void EnemySpawner::PickEnemyLocations(std::vector<engine::GameObject*> locations, int amount) {
	
	// Empty previous locations
	m_SpawnLocations.clear();

	std::shuffle(locations.begin(), locations.end(), m_RandomEngine);
	std::for_each(locations.begin(), locations.begin() + amount, [&](engine::GameObject* location) {
		location->GetComponent<SlidingComponent>()->HideEgg();
		location->GetComponent<SlidingComponent>()->m_Broken.AddObserver(this);
		m_SpawnLocations.emplace_back(location); 
	});
}

void EnemySpawner::SpawnEnemy() {
	if (m_SpawnLocations.size() > 0) {
		std::shuffle(m_SpawnLocations.begin(), m_SpawnLocations.end(), m_RandomEngine);

		// Spawn enemy
		engine::GameObject* enemy = CreateSnowBee(m_SpawnLocations[0]->GetWorldPosition());
		enemy->AttachTo(m_pOwner, true);
		enemy->GetComponent<StickyComponent>()->m_GotSquashed.AddObserver(this);
		enemy->GetComponent<Stunnable>()->m_GotSquashed.AddObserver(this);
		m_ActiveEnemies.push_back(enemy);

		// Destroy Ice block
		m_SpawnLocations[0]->Destroy();
		m_SpawnLocations.erase(std::remove(m_SpawnLocations.begin(), m_SpawnLocations.end(), m_SpawnLocations[0]), m_SpawnLocations.end());

		// Spawn sound
		engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/spawnBee.wav", 0.5f);

	}
}

void EnemySpawner::OnNotify(engine::GameObject* object) {

	m_ActiveEnemies.erase(std::remove(m_ActiveEnemies.begin(), m_ActiveEnemies.end(), object), m_ActiveEnemies.end());

	// Reward points
	PointManager::GetInstance().AddScore(500);

	// Spawn sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/beeKilled.wav", 0.5f);
}

void EnemySpawner::OnNotify(SlidingComponent* component) {

	m_SpawnLocations.erase(std::remove(m_SpawnLocations.begin(), m_SpawnLocations.end(), component->GetOwner()), m_SpawnLocations.end());

	// Reward points
	PointManager::GetInstance().AddScore(500);

	// Spawn sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/beeDie.wav", 0.5f);
}

std::vector<engine::GameObject*> EnemySpawner::GetEnemies() const {
	return m_ActiveEnemies;
}

void EnemySpawner::AddPlayerEnemy(engine::GameObject* player) {
	m_ActiveEnemies.push_back(player);
}