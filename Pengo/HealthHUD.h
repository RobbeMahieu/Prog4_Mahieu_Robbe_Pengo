#pragma once
#include "Component.h"
#include <memory>
#include "Observer.h"
#include "TextRenderComponent.h"

namespace pengo {

	class HealthComponent;

	class HealthHUD : public engine::Component, public engine::Observer<int>
	{
		public:
			HealthHUD(engine::GameObject* pOwner, HealthComponent* pHealthComponent);
			virtual ~HealthHUD() = default;

			HealthHUD(const HealthHUD& other) = delete;
			HealthHUD(HealthHUD&& other) = delete;
			HealthHUD& operator=(const HealthHUD& other) = delete;
			HealthHUD& operator=(HealthHUD&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}

			virtual void OnNotify(int health) override;

		private:
			engine::TextRenderComponent* m_pTextRenderer;

	};
}

