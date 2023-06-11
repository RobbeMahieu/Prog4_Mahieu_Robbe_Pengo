#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <SubjectObserver.h>
#include "CollisionComponent.h"

namespace pengo {

	class IceBlockState;

	// Might not be the best name fot this component anymore
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

			void Push(glm::vec2 direction);
			void HideEgg();

			void OnNotify(CollisionComponent* other) override;

			engine::Subject<engine::GameObject*> m_Broken;


		private:
			void TransitionTo(IceBlockState* state);

			IceBlockState* m_pState;
	};
	
}

