#include "StunComponent.h"
#include "CollisionComponent.h"
#include "Stunnable.h"
#include "PointManager.h"

using namespace pengo;

StunComponent::StunComponent(engine::GameObject* pOwner) 
	: Component(pOwner)
{
}

void StunComponent::StunEnemies(glm::vec2 direction) {
	
	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	glm::vec3 pos{ m_pOwner->GetLocalPosition() };
	pos.x += direction.x * 1;
	pos.y += direction.y * 1;
	m_pOwner->SetLocalPosition(pos);


	// Get all enemies colliding
	std::vector<CollisionHit> hitResult{ collider->GetAllColliding({}, {CollisionLayer::ENEMY}) };
	pos.x -= direction.x * 1;
	pos.y -= direction.y * 1;
	m_pOwner->SetLocalPosition(pos);

	// Stun them
	for (const CollisionHit& hit : hitResult) {
		hit.object->GetComponent<Stunnable>()->GetStunned();
	}

	// Reward points
	PointManager::GetInstance().AddScore(int(50 * hitResult.size()));
}