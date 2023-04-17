#pragma once
#include "Component.h"
#include <memory>
#include "Observer.h"

namespace dae {
	class GameObject;
}

class HealthComponent;
class TextRenderComponent;

class HealthHUD : public Component, public Observer
{
	public:
		HealthHUD(dae::GameObject* pOwner, HealthComponent* pHealthComponent);
		virtual ~HealthHUD() = default;

		HealthHUD(const HealthHUD& other) = delete;
		HealthHUD(HealthHUD&& other) = delete;
		HealthHUD& operator=(const HealthHUD& other) = delete;
		HealthHUD& operator=(HealthHUD&& other) = delete;

		virtual void Update([[maybe_unused]] float elapsedSec) {}
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

		virtual void OnNotify(EventType event, dae::GameObject* invokingObject) override;

	private:
		HealthComponent* m_pHealthComponent;
		TextRenderComponent* m_pTextRenderer;
};

