#pragma once
#include "Component.h"
#include "Subject.h"

class HealthComponent final : public Component
{
	public:
		HealthComponent(dae::GameObject* pOwner, int startingHealth);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update(float /*elapsedSec*/) {}
		virtual void FixedUpdate(float /*elapsedSec*/) {}

		void TakeDamage(int amount);
		int GetHealth();

	private:
		int m_Health;

		void SetHealth(int newHealth);

	public:
		Subject<int> HealthChanged;

};

