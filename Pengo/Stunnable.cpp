#include "Stunnable.h"
#include <GameTime.h>
#include "KillPlayerComponent.h"
#include <GameServiceLocator.h>
#include "AIMovement.h"

using namespace pengo;

Stunnable::Stunnable(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_AccuTime{ 0.0f }
	, m_StunTime{ 5.0f }
	, m_State{ State::Free }
{
	m_pOwner->GetComponent<CollisionComponent>()->OnCollision.AddObserver(this);
}

void Stunnable::Update() {

	if (m_State == State::Crushed) {
		m_GotSquashed.Broadcast(m_pOwner);
		m_pOwner->Destroy();
	}

	if (m_State != State::Stunned) { return; }

	m_AccuTime += engine::GameTime::GetInstance().GetElapsedSec();

	if (m_AccuTime >= m_StunTime) {
		m_State = State::Free;

		KillPlayerComponent* killComponent{ m_pOwner->GetComponent<KillPlayerComponent>() };
		if (killComponent) {
			killComponent->Enable(true);
		}

		AIMovement* movement = m_pOwner->GetComponent<AIMovement>();
		if (movement) {
			movement->EnableMovement(true);
		}
	}
}

void Stunnable::GetStunned(){

	m_AccuTime = 0.0f;

	KillPlayerComponent* killComponent{ m_pOwner->GetComponent<KillPlayerComponent>() };
	if (killComponent) {
		killComponent->Enable(false);
	}

	AIMovement* movement = m_pOwner->GetComponent<AIMovement>();
	if (movement) {
		movement->EnableMovement(false);
	}

	// Stunned sound
	engine::GameServiceLocator::GetSoundSystem().Play("../Data/Sounds/beeStunned.wav", 0.5f);
	m_State = State::Stunned;
}

void Stunnable::OnNotify(CollisionComponent* other) {
	if (m_State != State::Stunned) { return; }

	if (other->GetLayer() == CollisionLayer::PLAYER) {
		m_State = State::Crushed;
	}
}