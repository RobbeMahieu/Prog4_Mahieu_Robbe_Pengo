#include "DiamondSpawner.h"
#include "SlidingComponent.h"
#include "PointManager.h"
#include <GameServiceLocator.h>

using namespace pengo;

DiamondSpawner::DiamondSpawner(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_RandomEngine{ std::random_device{}() }
	, m_BonusAwarded{ false }
{
}

void DiamondSpawner::PickDiamondLocations(std::vector<engine::GameObject*> locations, int amount) {

	// Empty previous locations
	m_pDiamonds.clear();
	m_BonusAwarded = false;

	// Remove eggs from options
	std::vector<engine::GameObject*> iceBlocks{};
	std::copy_if(locations.begin(), locations.end(), std::inserter(iceBlocks, iceBlocks.begin()), [](engine::GameObject* location) {
		return !location->GetComponent<SlidingComponent>()->IsEgg();
	});

	std::shuffle(iceBlocks.begin(), iceBlocks.end(), m_RandomEngine);
	std::for_each(iceBlocks.begin(), iceBlocks.begin() + amount, [&](engine::GameObject* location) {
		location->GetComponent<SlidingComponent>()->SetDiamond();
		m_pDiamonds.emplace_back(location);
	});
}

void DiamondSpawner::Update() {

	if (m_BonusAwarded || m_pDiamonds.size() == 0) { return; }

	// Check if they are in the same row/collumn
	bool sameLine{ true };
	bool sameRow{ true };
	for (int i{ 0 }; i < int(m_pDiamonds.size() - 1); ++i) {
		glm::vec3 pos1{ m_pDiamonds[i]->GetWorldPosition() };
		glm::vec3 pos2{ m_pDiamonds[i+1]->GetWorldPosition()};

		sameLine &= pos1.y == pos2.y;
		sameRow &= pos1.x == pos2.x;

		if (!sameLine && !sameRow) { break; }
	}

	if (!sameLine && !sameRow) { return; }

	// Sort in order of their position
	std::sort(m_pDiamonds.begin(), m_pDiamonds.end(), [&](engine::GameObject* a, engine::GameObject* b) {
		glm::vec3 posA{ a->GetWorldPosition() };
		glm::vec3 posB{ b->GetWorldPosition() };

		return (sameLine) ? posA.x > posB.x : posA.y > posB.y;
	});

	for (int i{ 0 }; i < int(m_pDiamonds.size() - 1); ++i) {
		glm::vec3 pos1{ m_pDiamonds[i]->GetWorldPosition() };
		glm::vec3 pos2{ m_pDiamonds[i + 1]->GetWorldPosition() };

		sameLine &= pos1.x - pos2.x == 32;
		sameRow &= pos1.y - pos2.y == 32;

		if (!sameLine && !sameRow) { break; }
	}

	if (!sameLine && !sameRow) { return; }

	// Blocks are alligned!
	PointManager::GetInstance().AddScore(5000);

	// Bonus sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/diamonds.wav", 0.5f);

	m_BonusAwarded = true;
	m_DiamondsAlligned.Broadcast(this);
}

