#include "HealthComponent.h"
#include "GameObject.h"

using namespace pengo;

HealthComponent::HealthComponent(engine::GameObject* pOwner, int startingHealth)
	: Component(pOwner)
	, m_Health{startingHealth}
{
}

void HealthComponent::TakeDamage(int amount) {
	SetHealth(m_Health - amount);
}

void HealthComponent::SetHealth(int newHealth) {
	m_Health = newHealth;
	HealthChanged.Broadcast(this, m_Health);

	if (m_Health < 0) {
		m_pOwner->Destroy();
	}
}

int HealthComponent::GetHealth() {
	return m_Health;
}