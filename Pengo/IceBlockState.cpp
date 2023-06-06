#include "IceBlockState.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "PushComponent.h"

using namespace pengo;

// -- Base State
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

IceBlockState* Sliding::Update(float elapsedSec) {
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

IceBlockState* Idle::HandleCollision(CollisionComponent* collider) {
	
	PushComponent* pushComponent = collider->GetOwner()->GetComponent<PushComponent>();
	if (!pushComponent || !pushComponent->CanPush()) {
		return nullptr;
	}

	glm::vec3 distanceBetween{ m_pOwner->GetWorldPosition() - collider->GetOwner()->GetWorldPosition() };

	glm::vec2 direction{ (abs(distanceBetween.x) > abs(distanceBetween.y)) ? glm::vec2{1,0} : glm::vec2{0,1} };
	glm::vec2 sign{ distanceBetween.x / abs(distanceBetween.x),distanceBetween.y / abs(distanceBetween.y) };
	direction *= sign;

	return new Sliding(m_pOwner, m_Speed, direction);

}

// -- Break State --
Break::Break(engine::GameObject* pOwner)
	: IceBlockState(pOwner)
{
	m_pOwner->Destroy();
}