#include "EnemySpawner.h"
#include "SnowBee.h"
#include "AIMovement.h"
#include "SlidingComponent.h"

using namespace pengo;

EnemySpawner::EnemySpawner(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_RandomEngine{ std::random_device{}() }
	, m_EnemyCounter{ 0 }
	, m_EnemiesKilled{}

{
}

void EnemySpawner::Update() {
	if (m_ActiveEnemies.size() < 3) {
		SpawnEnemy();
	}

	if (m_ActiveEnemies.size() == 0) {
		m_EnemiesKilled.Broadcast();
	}
}

void EnemySpawner::PickEnemyLocations(std::vector<engine::GameObject*> locations, int amount) {
	
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
		enemy->GetComponent<AIMovement>()->m_pKilled.AddObserver(this);
		m_ActiveEnemies.push_back(enemy);

		// Destroy Ice block
		m_SpawnLocations[0]->Destroy();
		m_SpawnLocations.erase(std::remove(m_SpawnLocations.begin(), m_SpawnLocations.end(), m_SpawnLocations[0]), m_SpawnLocations.end());


	}
}

void EnemySpawner::OnNotify(AIMovement* component) {

	m_ActiveEnemies.erase(std::remove(m_ActiveEnemies.begin(), m_ActiveEnemies.end(), component->GetOwner()), m_ActiveEnemies.end());
}

void EnemySpawner::OnNotify(engine::GameObject* object) {

	m_SpawnLocations.erase(std::remove(m_SpawnLocations.begin(), m_SpawnLocations.end(), object), m_SpawnLocations.end());
}

std::vector<engine::GameObject*> EnemySpawner::GetEnemies() const {
	return m_ActiveEnemies;
}