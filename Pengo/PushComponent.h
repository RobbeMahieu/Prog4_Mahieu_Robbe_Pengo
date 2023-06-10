#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include "Keyboard.h"
#include "XBoxController.h"

namespace pengo {

	class PushCommand;
	class SlidingComponent;

	class PushComponent : public engine::Component
	{
		public:
			PushComponent(engine::GameObject* pOwner, engine::Keyboard* device);
			PushComponent(engine::GameObject* pOwner, engine::XBoxController* device);
			virtual ~PushComponent() = default;

			PushComponent(const PushComponent& other) = delete;
			PushComponent(PushComponent&& other) = delete;
			PushComponent& operator=(const PushComponent& other) = delete;
			PushComponent& operator=(PushComponent&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {};

		private:
			PushComponent(engine::GameObject* pOwner);

			PushCommand* m_Push;
	};

}