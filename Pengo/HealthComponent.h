#pragma once
#include "Component.h"
#include "Subject.h"

namespace pengo {

	class HealthComponent final : public engine::Component
	{
		public:
			HealthComponent(engine::GameObject* pOwner, int startingHealth);
			virtual ~HealthComponent() = default;

			HealthComponent(const HealthComponent& other) = delete;
			HealthComponent(HealthComponent&& other) = delete;
			HealthComponent& operator=(const HealthComponent& other) = delete;
			HealthComponent& operator=(HealthComponent&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}

			void TakeDamage(int amount);
			int GetHealth();

		private:
			int m_Health;

			void SetHealth(int newHealth);

		public:
			engine::Subject<int> HealthChanged;

	};
}
