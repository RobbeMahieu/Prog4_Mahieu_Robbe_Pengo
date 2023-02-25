#pragma once
#include "Component.h"

class RenderComponent : public dae::Component
{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update([[maybe_unused]] float elapsedSec) override {};
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) override {};
		virtual void Render() const = 0;
};

