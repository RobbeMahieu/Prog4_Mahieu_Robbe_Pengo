#include "SlidingComponent.h"
#include "GameObject.h"

SlidingComponent::SlidingComponent(dae::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
	, m_MovementDirection{ glm::vec2{0,0} }
	, m_IsSliding{ false }
{
}

void SlidingComponent::Update(float elapsedSec) {
	
	if (m_IsSliding) {
		glm::vec3 pos = m_pOwner->GetLocalPosition();
		pos.x += m_MovementSpeed * elapsedSec * m_MovementDirection.x;
		pos.y += m_MovementSpeed * elapsedSec * m_MovementDirection.y;
		m_pOwner->SetLocalPosition(pos);
	}
}

void SlidingComponent::StartSliding(glm::vec2 direction) {
	m_MovementDirection = direction;
	m_IsSliding = true;

	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	if (collider) {
		collider->OnCollision.AddObserver(this);
	}
}

void SlidingComponent::OnNotify(CollisionComponent* other) {
	m_MovementDirection = glm::vec2{ 0,0 };
	m_IsSliding = false;

	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	if (collider) {
		collider->OnCollision.RemoveObserver(this);
	}
}