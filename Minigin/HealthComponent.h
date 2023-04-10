#pragma once
#include "Component.h"
#include <memory>

class Keyboard;

class HealthComponent : public Component
{
	public:
		HealthComponent(dae::GameObject* pOwner, int startingHealth, Keyboard* device);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update([[maybe_unused]] float elapsedSec) {}
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

		void TakeDamage(int amount);
		int GetHealth();

	protected:
		int m_StartHealth;
		int m_CurrentHealth;
};

