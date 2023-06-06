#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include "Keyboard.h"
#include "XBoxController.h"

namespace pengo {

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

			virtual void Update(float /*elapsedSec*/) {};
			virtual void FixedUpdate(float /*elapsedSec*/) {}

			bool CanPush() const;
			void EnablePush(bool enable);

		private:
			bool m_CanPush{ false };

	};

}