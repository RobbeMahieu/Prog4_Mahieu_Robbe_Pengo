#pragma once
#include "Component.h"
#include <memory>
#include "Observer.h"

namespace dae {
	class GameObject;
}

class TextRenderComponent;
class HealthComponent;

class HealthHUD : public Component, public Observer<int>
{
	public:
		HealthHUD(dae::GameObject* pOwner, HealthComponent* pHealthComponent);
		virtual ~HealthHUD() = default;

		HealthHUD(const HealthHUD& other) = delete;
		HealthHUD(HealthHUD&& other) = delete;
		HealthHUD& operator=(const HealthHUD& other) = delete;
		HealthHUD& operator=(HealthHUD&& other) = delete;

		virtual void Update(float /*elapsedSec*/) {}
		virtual void FixedUpdate(float /*elapsedSec*/) {}

		virtual void OnNotify(int health) override;

	private:
		TextRenderComponent* m_pTextRenderer;
};

