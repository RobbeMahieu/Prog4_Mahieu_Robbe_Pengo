#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include <Keyboard.h>
#include <XBoxController.h>
#include <memory>
#include <SubjectObserver.h>

namespace pengo {

	class PushCommand;

	class PushComponent final : public engine::Component
	{
		public:
			PushComponent(engine::GameObject* pOwner, engine::Keyboard* device);
			PushComponent(engine::GameObject* pOwner, engine::XBoxController* device);
			virtual ~PushComponent();

			PushComponent(const PushComponent& other) = delete;
			PushComponent(PushComponent&& other) = delete;
			PushComponent& operator=(const PushComponent& other) = delete;
			PushComponent& operator=(PushComponent&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {};

		private:
			PushComponent(engine::GameObject* pOwner);

			std::unique_ptr<PushCommand> m_Push;
	};

}