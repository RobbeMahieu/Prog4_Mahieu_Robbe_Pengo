#include "KillPlayerComponent.h"
#include "PlayerMovement.h"
#include "HealthComponent.h"

using namespace pengo;

KillPlayerComponent::KillPlayerComponent(engine::GameObject* pOwner)
	: Component(pOwner)
{
	m_pOwner->GetComponent<CollisionComponent>()->OnCollision.AddObserver(this);
}

void KillPlayerComponent::OnNotify(CollisionComponent* other) {

	if (!m_Enabled) { return; }

	if (other->GetOwner()->GetComponent<PlayerMovement>()) {
		other->GetOwner()->GetComponent<HealthComponent>()->TakeDamage(1);
	}
}

void KillPlayerComponent::Enable(bool enable) {
	m_Enabled = enable;
}