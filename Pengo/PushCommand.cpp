#include "PushCommand.h"
#include "SlidingComponent.h"
#include <unordered_set>
#include "CollisionComponent.h"
#include "StunComponent.h"

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
		glm::vec3 pos{ m_pOwner->GetWorldPosition() };

		for (SlidingComponent* block : iceBlocks) {
			glm::vec3 otherPos{ block->GetOwner()->GetWorldPosition()};
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

	// Calculate direction
	glm::vec3 distanceBetween{ m_ClosestIce->GetOwner()->GetWorldPosition() - m_pOwner->GetWorldPosition() };

	glm::vec2 direction = (abs(distanceBetween.x) > abs(distanceBetween.y)) ? glm::vec2{ 1,0 } : glm::vec2{ 0,1 };

	// Divide by 0 protection
	if (distanceBetween.x == 0) {
		distanceBetween.x = 1;
	}
	if (distanceBetween.y == 0) {
		distanceBetween.y = 1;
	}

	glm::vec2 sign{ distanceBetween.x / abs(distanceBetween.x), distanceBetween.y / abs(distanceBetween.y) };
	direction *= sign;

	m_ClosestIce->Push(direction);
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

		glm::vec4 bounds{ m_pOwner->GetComponent<CollisionComponent>()->GetBounds()};
		glm::vec3 pos{ bounds.x + bounds.z / 2, bounds.y + bounds.w / 2, 0 };

		for (StunComponent* block : walls) {
			bounds = block->GetOwner()->GetComponent<CollisionComponent>()->GetBounds();
			glm::vec3 otherPos{ bounds.x + bounds.z / 2, bounds.y + bounds.w / 2, 0 };
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
	glm::vec3 pos{ bounds.x + bounds.z / 2, bounds.y + bounds.w / 2, 0 };

	bounds = m_ClosestWall->GetOwner()->GetComponent<CollisionComponent>()->GetBounds();
	glm::vec3 otherPos{ bounds.x + bounds.z / 2, bounds.y + bounds.w / 2, 0 };

	glm::vec3 distanceBetween{ otherPos - pos };
	glm::vec2 direction = (abs(distanceBetween.x) < abs(distanceBetween.y)) ? glm::vec2{ 1,0 } : glm::vec2{ 0,1 };

	// Divide by 0 protection
	if (distanceBetween.x == 0) {
		distanceBetween.x = 1;
	}
	if (distanceBetween.y == 0) {
		distanceBetween.y = 1;
	}

	glm::vec2 sign{ distanceBetween.x / abs(distanceBetween.x), distanceBetween.y / abs(distanceBetween.y) };
	direction *= sign;

	m_ClosestWall->StunEnemies(-direction);
}