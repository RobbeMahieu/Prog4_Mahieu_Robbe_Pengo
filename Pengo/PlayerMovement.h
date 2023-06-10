#pragma once
#include "Component.h"
#include "Keyboard.h"
#include "XBoxController.h"

namespace pengo {

	class MoveCommand;
	class PushCommand;

	class PlayerMovement : public engine::Component
	{
		public:
			PlayerMovement(engine::GameObject* pOwner, float speed, engine::Keyboard* device);
			PlayerMovement(engine::GameObject* pOwner, float speed, engine::XBoxController* device);
			virtual ~PlayerMovement() = default;

			PlayerMovement(const PlayerMovement& other) = delete;
			PlayerMovement(PlayerMovement&& other) = delete;
			PlayerMovement& operator=(const PlayerMovement& other) = delete;
			PlayerMovement& operator=(PlayerMovement&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {}

		private:
			PlayerMovement(engine::GameObject* pOwner, float speed);

			// Move Commands (will be used to unbind in the future)
			MoveCommand* m_MoveUp;
			MoveCommand* m_MoveDown;
			MoveCommand* m_MoveLeft;
			MoveCommand* m_MoveRight;
	};
}

