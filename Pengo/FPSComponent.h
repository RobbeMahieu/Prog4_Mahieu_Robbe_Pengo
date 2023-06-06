#pragma once
#include "Component.h"
#include <string>

namespace pengo {

	class FPSComponent : public engine::Component
	{
	public:
		FPSComponent(engine::GameObject* pOwner);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate(float /*elapsedSec*/) {}

	protected:
		float m_Fps;

	};
}

