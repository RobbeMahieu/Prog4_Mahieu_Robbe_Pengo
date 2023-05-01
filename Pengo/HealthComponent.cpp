#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(dae::GameObject* pOwner, int startingHealth)
	: Component(pOwner)
	, m_Health{startingHealth}
{
}

void HealthComponent::TakeDamage(int amount) {
	m_Health -= amount;
	HealthChanged.Broadcast(m_Health);
}

void HealthComponent::SetHealth(int newHealth) {
	m_Health = newHealth;
	HealthChanged.Broadcast(m_Health);
}

int HealthComponent::GetHealth() {
	return m_Health;
}