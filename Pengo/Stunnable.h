#pragma once
#include <Component.h>
#include <SubjectObserver.h>

namespace pengo {

	class CollisionComponent;
	class SlidingComponent;

	class Stunnable final : public engine::Component, engine::Observer<CollisionComponent*>
	{

		enum State {
			Free,
			Stunned,
			Crushed,
		};

		public:
			Stunnable(engine::GameObject* pOwner);
			virtual ~Stunnable() = default;

			Stunnable(const Stunnable& other) = delete;
			Stunnable(Stunnable&& other) = delete;
			Stunnable& operator=(const Stunnable& other) = delete;
			Stunnable& operator=(Stunnable&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {};

			void GetStunned();
			virtual void OnNotify(CollisionComponent* other);

			engine::Subject<engine::GameObject*> m_GotSquashed;

		private:
			float m_StunTime;
			float m_AccuTime;
			State m_State;
	};

}