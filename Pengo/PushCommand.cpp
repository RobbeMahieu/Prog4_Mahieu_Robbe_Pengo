#include "PushCommand.h"
#include "SlidingComponent.h"
#include <unordered_set>
#include "CollisionComponent.h"

using namespace pengo;

PushCommand::PushCommand(engine::GameObject* pOwner)
	: Command()
	, m_pOwner{ pOwner }
	, m_ClosestIce{ nullptr }
{
}

void PushCommand::Execute() {
	if (!CanPush()) { return; }

	// Calculate direction
	glm::vec3 distanceBetween{ m_ClosestIce->GetOwner()->GetWorldPosition() - m_pOwner->GetWorldPosition() };

	glm::vec2 direction = (abs(distanceBetween.x) > abs(distanceBetween.y)) ? glm::vec2{1,0} : glm::vec2{0,1};

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
