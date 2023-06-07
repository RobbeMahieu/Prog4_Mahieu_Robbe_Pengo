#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Keyboard.h"
#include "XBoxController.h"



namespace pengo {

	class MoveCommand;

	class BasicMovement : public engine::Component
	{
		public:
			BasicMovement(engine::GameObject* pOwner, float speed, engine::Keyboard* device);
			BasicMovement(engine::GameObject* pOwner, float speed, engine::XBoxController* device);
			virtual ~BasicMovement() = default;

			BasicMovement(const BasicMovement& other) = delete;
			BasicMovement(BasicMovement&& other) = delete;
			BasicMovement& operator=(const BasicMovement& other) = delete;
			BasicMovement& operator=(BasicMovement&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {}

		private:
			BasicMovement(engine::GameObject* pOwner, float speed);

			// Move Commands (will be used to unbind in the future)
			MoveCommand* m_MoveUp;
			MoveCommand* m_MoveDown;
			MoveCommand* m_MoveLeft;
			MoveCommand* m_MoveRight;
	};
}

