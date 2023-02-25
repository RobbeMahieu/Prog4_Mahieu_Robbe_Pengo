#pragma once
#include "Component.h"
#include <string>

class FPSComponent : public dae::Component
{
		public:
			FPSComponent(std::string textRenderName);
			virtual ~FPSComponent() = default;

			FPSComponent(const FPSComponent& other) = delete;
			FPSComponent(FPSComponent&& other) = delete;
			FPSComponent& operator=(const FPSComponent& other) = delete;
			FPSComponent& operator=(FPSComponent&& other) = delete;

			virtual void Update(float elapsedSec);
			virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

		protected:
			float m_Fps{ 0.0f };
			std::string m_TextRenderName{ "" };

};

