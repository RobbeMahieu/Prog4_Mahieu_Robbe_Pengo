#include "DiamondSpawner.h"
#include "SlidingComponent.h"

using namespace pengo;

DiamondSpawner::DiamondSpawner(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_RandomEngine{ std::random_device{}() }
{
}

void DiamondSpawner::PickDiamondLocations(std::vector<engine::GameObject*> locations, int amount) {

	// Empty previous locations
	m_pDiamonds.clear();

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

	// Check if they are in the same row/collumn
	bool sameLine{ true };
	bool sameRow{ true };
	for (int i{ 0 }; i < int(m_pDiamonds.size() - 1); ++i) {
		glm::vec3 pos1{ m_pDiamonds[i]->GetWorldPosition() };
		glm::vec3 pos2{ m_pDiamonds[i+1]->GetWorldPosition()};

		sameLine |= pos1.x == pos2.x;
		sameRow |= pos1.y == pos2.y;

		if (!sameLine && !sameRow) {
			break;
		}
	}

	if (!sameLine && !sameRow) {
		return;
	}

	// Either same line or row

}

