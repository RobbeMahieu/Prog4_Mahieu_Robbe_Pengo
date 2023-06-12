#pragma once
#include <Component.h>
#include <SubjectObserver.h>


namespace pengo {

	class CollisionComponent;
	class SlidingComponent;
	
	class StickyComponent : public engine::Component, engine::Observer<CollisionComponent*>
	{
		enum State {
			Free,
			Stuck,
			Crushed,
		};

		public:
			StickyComponent(engine::GameObject* pOwner);
			virtual ~StickyComponent() = default;

			StickyComponent(const StickyComponent& other) = delete;
			StickyComponent(StickyComponent&& other) = delete;
			StickyComponent& operator=(const StickyComponent& other) = delete;
			StickyComponent& operator=(StickyComponent&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {};

			virtual void OnNotify(CollisionComponent* other);

			engine::Subject<engine::GameObject*> m_GotSquashed;

		private:
			State m_State;
			SlidingComponent* m_pBlock;
	};
}