#pragma once
#include "Component.h"
#include <string>

class FPSComponent : public Component
{
	public:
		FPSComponent(dae::GameObject* pOwner);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

	protected:
		float m_Fps;

};

