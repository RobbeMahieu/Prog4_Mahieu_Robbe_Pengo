#include "StickyComponent.h"
#include "CollisionComponent.h"
#include "SlidingComponent.h"
#include "AIMovement.h"
#include "PlayerMovement.h"

using namespace pengo;

StickyComponent::StickyComponent(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_State{ State::Free }
	, m_pBlock{ nullptr }
{
	m_pOwner->GetComponent<CollisionComponent>()->OnCollision.AddObserver(this);
}

void StickyComponent::Update() {
	if (m_State == State::Crushed) {
		m_GotSquashed.Broadcast(m_pOwner);
		m_pOwner->Destroy();
	}
}

void StickyComponent::OnNotify(CollisionComponent* other) {
	
	if (m_State == State::Free && other->GetLayer() == CollisionLayer::DYNAMIC) {
		m_pBlock = other->GetOwner()->GetComponent<SlidingComponent>();

		// For AI
		AIMovement* movementAI = m_pOwner->GetComponent<AIMovement>();
		if (movementAI) {
			movementAI->EnableMovement(false);
		}

		// For Player
		PlayerMovement* movementPlayer = m_pOwner->GetComponent<PlayerMovement>();
		if (movementPlayer) {
			movementPlayer->EnableMovement(false);
		}
		m_State = State::Stuck;
	}

	if (m_State == State::Stuck && other->GetLayer() == CollisionLayer::STATIC) {
		m_State = State::Crushed;
	}
}