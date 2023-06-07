#pragma once
#include <Command.h>
#include "GameObject.h"

namespace pengo {

	class MoveCommand final : public engine::Command
	{
		public:
			explicit MoveCommand(engine::GameObject* object, glm::vec2 direction, float speed);
			virtual ~MoveCommand() = default;

			MoveCommand(const MoveCommand& other) = delete;
			MoveCommand(MoveCommand&& other) = delete;
			MoveCommand& operator=(const MoveCommand& other) = delete;
			MoveCommand& operator=(MoveCommand&& other) = delete;

			virtual void Execute() override;

		private:
			engine::GameObject* m_pObject;
			glm::vec2 m_Direction;
			float m_Speed;


	};
}

