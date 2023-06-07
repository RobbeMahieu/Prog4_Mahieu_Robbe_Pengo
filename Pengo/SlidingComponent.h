#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include "Observer.h"
#include "CollisionComponent.h"

namespace pengo {

	class IceBlockState;

	class SlidingComponent : public engine::Component, public engine::Observer<CollisionComponent*>
	{
		public:
			SlidingComponent(engine::GameObject* pOwner, float speed);
			virtual ~SlidingComponent();

			SlidingComponent(const SlidingComponent& other) = delete;
			SlidingComponent(SlidingComponent&& other) = delete;
			SlidingComponent& operator=(const SlidingComponent& other) = delete;
			SlidingComponent& operator=(SlidingComponent&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {}

			void OnNotify(CollisionComponent* other) override;

		protected:
			IceBlockState* m_pState;
	};
	
}

