#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Keyboard.h"
#include "XBoxController.h"



namespace pengo {

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

			virtual void Update(float elapsedSec);
			virtual void FixedUpdate(float /*elapsedSec*/) {}

			void Move(glm::vec2 direction);

		protected:
			float m_MovementSpeed;
			glm::vec2 m_MovementDirection{ 0,0 };
	};
}

