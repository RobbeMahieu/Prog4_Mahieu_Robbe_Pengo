#pragma once
#include <Component.h>
#include <GameObject.h>
#include <SubjectObserver.h>
#include "CollisionComponent.h"

namespace pengo {

	class KillPlayerComponent :public engine::Component, engine::Observer<CollisionComponent*>
	{
		public:
			KillPlayerComponent(engine::GameObject* pOwner);
			virtual ~KillPlayerComponent() = default;

			KillPlayerComponent(const KillPlayerComponent& other) = delete;
			KillPlayerComponent(KillPlayerComponent&& other) = delete;
			KillPlayerComponent& operator=(const KillPlayerComponent& other) = delete;
			KillPlayerComponent& operator=(KillPlayerComponent&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {}

			virtual void OnNotify(CollisionComponent* other);
			
			void Enable(bool enable);

		private:
			bool m_Enabled;

	};
}



