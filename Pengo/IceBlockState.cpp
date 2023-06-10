#include "IceBlockState.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "PushComponent.h"
#include "GameTime.h"

using namespace pengo;

// -- Base State --
IceBlockState::IceBlockState(engine::GameObject* pOwner) 
	: m_pOwner{ pOwner }
{
}

// -- Sliding State --

Sliding::Sliding(engine::GameObject* pOwner, float speed, const glm::vec2& direction)
	: IceBlockState(pOwner)
	, m_SlidingSpeed{speed}
	, m_Direction{direction}
{
}

void Sliding::OnEnter() {
	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	collider->SetType(PhysicsType::MOVABLE);
}

IceBlockState* Sliding::Update() {
	const float elapsedSec{ engine::GameTime::GetInstance().GetElapsedSec() };

	glm::vec3 pos = m_pOwner->GetLocalPosition();
	pos.x += m_SlidingSpeed * elapsedSec * m_Direction.x;
	pos.y += m_SlidingSpeed * elapsedSec * m_Direction.y;
	m_pOwner->SetLocalPosition(pos);
	return nullptr;
}

IceBlockState* Sliding::HandleCollision(CollisionComponent* collider) {
	return (collider->GetType() != PhysicsType::DYNAMIC) ? new Idle(m_pOwner, m_SlidingSpeed) : nullptr;
}

// Idle State --

Idle::Idle(engine::GameObject* pOwner, float speed)
	: IceBlockState(pOwner)
	, m_Speed{ speed }
{
}

void Idle::OnEnter() {
	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	collider->SetType(PhysicsType::STATIC);
}

IceBlockState* Idle::Push(glm::vec2 direction) {
	
	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	glm::vec4 bounds{ collider->GetBounds() };
	bounds.x += direction.x*1;
	bounds.y += direction.y*1;

	// Check for collision in moving direction
	bool isBlocked{ CollisionComponent::CheckCollision(bounds, {collider}).hit };

	// Start break
	if (isBlocked) {
		return new Break(m_pOwner);
	}

	// Start push
	return new Sliding(m_pOwner, m_Speed, direction);

}

// -- Break State --
Break::Break(engine::GameObject* pOwner)
	: IceBlockState(pOwner)
{
	m_pOwner->Destroy();
}