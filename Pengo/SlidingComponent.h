#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include "Observer.h"
#include "CollisionComponent.h"

class IceBlockState;

class SlidingComponent : public Component, public Observer<CollisionComponent*>
{
	public:
		SlidingComponent(dae::GameObject* pOwner, float speed);
		virtual ~SlidingComponent() = default;

		SlidingComponent(const SlidingComponent& other) = delete;
		SlidingComponent(SlidingComponent&& other) = delete;
		SlidingComponent& operator=(const SlidingComponent& other) = delete;
		SlidingComponent& operator=(SlidingComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

		void OnNotify(CollisionComponent* other) override;

	protected:
		IceBlockState* m_pState;
};

