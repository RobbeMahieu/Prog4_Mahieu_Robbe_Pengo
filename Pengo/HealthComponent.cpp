#include "HealthComponent.h"
#include "GameObject.h"

using namespace pengo;

HealthComponent::HealthComponent(engine::GameObject* pOwner, int startingHealth)
	: Component(pOwner)
	, m_Health{startingHealth}
{
}

void HealthComponent::TakeDamage(int amount) {
	m_Health -= amount;
	HealthChanged.Broadcast(m_Health);

	if (m_Health <= 0) {
		m_pOwner->Destroy();
	}
}

void HealthComponent::SetHealth(int newHealth) {
	m_Health = newHealth;
	HealthChanged.Broadcast(m_Health);

	if (m_Health <= 0) {
		m_pOwner->Destroy();
	}
}

int HealthComponent::GetHealth() {
	return m_Health;
}