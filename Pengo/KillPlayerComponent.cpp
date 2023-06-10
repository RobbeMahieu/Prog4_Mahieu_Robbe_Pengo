#include "KillPlayerComponent.h"
#include "PlayerMovement.h"

using namespace pengo;

KillPlayerComponent::KillPlayerComponent(engine::GameObject* pOwner)
	: Component(pOwner)
{
	m_pOwner->GetComponent<CollisionComponent>()->OnCollision.AddObserver(this);
}

void KillPlayerComponent::OnNotify(CollisionComponent* other) {
	if (other->GetOwner()->GetComponent<PlayerMovement>()) {
		other->GetOwner()->Destroy();
	}
}