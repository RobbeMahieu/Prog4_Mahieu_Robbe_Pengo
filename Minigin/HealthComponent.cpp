#include "HealthComponent.h"
#include "GameObject.h"
#include "EventManager.h"

#include "InputDevice.h"
#include "InputManager.h"

#include "Keyboard.h"

HealthComponent::HealthComponent(dae::GameObject* pOwner, int startingHealth)
	: Component(pOwner)
	, m_StartHealth{startingHealth}
	, m_CurrentHealth{startingHealth}
{
}

void HealthComponent::TakeDamage(int amount) {
	m_CurrentHealth -= amount;

	EventManager::GetInstance().Broadcast(EventType::PlayerDied, m_pOwner);

	if (m_CurrentHealth <= 0) {
		EventManager::GetInstance().Broadcast(EventType::GameOver, m_pOwner);
	}
}

int HealthComponent::GetHealth() {
	return m_CurrentHealth;
}