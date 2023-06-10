#pragma once
#include <Component.h>
#include <vector>
#include "CollisionComponent.h"
#include <memory>
#include <random>

namespace pengo {

	class MoveCommand;
	typedef std::pair<bool, std::unique_ptr<MoveCommand>> DirectionOption;

	class AIMovement : public engine::Component
	{
		public:
			AIMovement(engine::GameObject* pOwner, float speed);
			virtual ~AIMovement() = default;

			AIMovement(const AIMovement& other) = delete;
			AIMovement(AIMovement&& other) = delete;
			AIMovement& operator=(const AIMovement& other) = delete;
			AIMovement& operator=(AIMovement&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {}

		private:
			std::vector<DirectionOption> m_MovementOptions;
			MoveCommand* m_CurrentOption;
			std::unique_ptr<MoveCommand> m_FallbackOption;
			CollisionComponent* m_pCollider;

			// Random engine
			std::default_random_engine m_RandomEngine;
			std::uniform_real_distribution<float> m_RandomNumber;

			void ChooseDirection();
			void UpdateOptions();
	};
}


