#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <SubjectObserver.h>
#include "CollisionComponent.h"

namespace pengo {

	class IceBlockState;
	class Sliding;
	class Idle;
	class Break;


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
			void SetDiamond();

			bool IsEgg() const;
			bool IsDiamond() const;

			void OnNotify(CollisionComponent* other) override;

			engine::Subject<SlidingComponent*> m_Broken;

			// Give states access to variables
			friend class IceBlockState;
			friend class Sliding;
			friend class Idle;
			friend class Break;


		private:
			void TransitionTo(IceBlockState* state);

			IceBlockState* m_pState;
			float m_Speed;

			bool m_IsEgg;
			bool m_IsDiamond;
	};
	
}

