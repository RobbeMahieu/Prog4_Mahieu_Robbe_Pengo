#include "PushCommand.h"
#include "SlidingComponent.h"
#include <unordered_set>
#include "CollisionComponent.h"
#include "StunComponent.h"
#include "PointManager.h"
#include <GameServiceLocator.h>

using namespace pengo;

PushCommand::PushCommand(engine::GameObject* pOwner)
	: Command()
	, m_pOwner{ pOwner }
	, m_ClosestIce{ nullptr }
	, m_ClosestWall{ nullptr }
{
}

void PushCommand::Execute() {
	Push();
	Stun();
}

bool PushCommand::CanPush() {

	// Get all ice blocks
	const std::unordered_set<CollisionComponent*> colliders = m_pOwner->GetComponent<CollisionComponent>()->GetCollided();
	std::unordered_set<SlidingComponent*> iceBlocks{};
	std::transform(colliders.begin(), colliders.end(), std::inserter(iceBlocks, iceBlocks.begin()), [](const CollisionComponent* collider) {
		return collider->GetOwner()->GetComponent<SlidingComponent>();
	});
	
	// Remove the nullptrs
	iceBlocks.erase(nullptr);

	if (iceBlocks.size() > 0) {

		// Get closest iceblock
		float closestDistance{ FLT_MAX };
		glm::vec2 pos{ m_pOwner->GetComponent<CollisionComponent>()->GetCenter() };

		for (SlidingComponent* block : iceBlocks) {
			glm::vec2 otherPos{ block->GetOwner()->GetComponent<CollisionComponent>()->GetCenter() };
			float distance{ glm::distance(pos, otherPos) };
			if (distance < closestDistance) {
				m_ClosestIce = block;
				closestDistance = distance;
			}
		}

		return true;
	}

	return false;
}

void PushCommand::Push() {
	if (!CanPush()) { return; }

	glm::vec4 bounds{ m_pOwner->GetComponent<CollisionComponent>()->GetBounds() };
	glm::vec4 otherBounds{ m_ClosestIce->GetOwner()->GetComponent<CollisionComponent>()->GetBounds() };

	std::vector<std::pair<float, glm::vec2>> options{
		{ abs(bounds.x - otherBounds.x - otherBounds.z), { -1,0 }},
		{ abs(bounds.x + bounds.z - otherBounds.x), { 1,0 } },
		{ abs(bounds.y - otherBounds.y - otherBounds.w), { 0,-1 } },
		{ abs(bounds.y + bounds.w - otherBounds.y), { 0,1 } }
	};

	std::sort(options.begin(), options.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
	glm::vec2 direction{ options[0].second };

	m_ClosestIce->Push(direction);

	// Reward points
	PointManager::GetInstance().AddScore(50);
}

bool PushCommand::CanStun() {

	// Get all walls blocks
	const std::unordered_set<CollisionComponent*> colliders = m_pOwner->GetComponent<CollisionComponent>()->GetCollided();
	std::unordered_set<StunComponent*> walls{};
	std::transform(colliders.begin(), colliders.end(), std::inserter(walls, walls.begin()), [](const CollisionComponent* collider) {
		return collider->GetOwner()->GetComponent<StunComponent>();
		});

	// Remove the nullptrs
	walls.erase(nullptr);

	if (walls.size() > 0) {

		// Get closest wall
		float closestDistance{ FLT_MAX };

		glm::vec2 pos{ m_pOwner->GetComponent<CollisionComponent>()->GetCenter()};

		for (StunComponent* block : walls) {
			glm::vec2 otherPos{ block->GetOwner()->GetComponent<CollisionComponent>()->GetCenter() };
			float distance{ glm::distance(pos, otherPos) };
			if (distance < closestDistance) {
				m_ClosestWall = block;
				closestDistance = distance;
			}
		}

		return true;
	}

	return false;
}

void PushCommand::Stun() {
	if (!CanStun()) { return; }

	// Calculate direction
	glm::vec4 bounds{ m_pOwner->GetComponent<CollisionComponent>()->GetBounds() };
	glm::vec4 otherBounds{ m_ClosestWall->GetOwner()->GetComponent<CollisionComponent>()->GetBounds() };

	std::vector<std::pair<float, glm::vec2>> options{
		{ abs(bounds.x - otherBounds.x - otherBounds.z), { 1,0 }},
		{ abs(bounds.x + bounds.z - otherBounds.x), { -1,0 } },
		{ abs(bounds.y - otherBounds.y - otherBounds.w), { 0,1 } },
		{ abs(bounds.y + bounds.w - otherBounds.y), { 0,-1 } }
	};

	std::sort(options.begin(), options.end(), [](const auto& a, const auto& b) {
		return a.first < b.first;
	});

	glm::vec2 direction{ options[0].second };
	
	m_ClosestWall->StunEnemies(direction);

	// Push wall sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/pushWall.wav", 0.5f);
}