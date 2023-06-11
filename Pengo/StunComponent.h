#pragma once
#include <Component.h>
#include <glm/glm.hpp>

namespace pengo {

	class StunComponent : public engine::Component
	{
		public:
			StunComponent(engine::GameObject* pOwner);
			virtual ~StunComponent() = default;

			StunComponent(const StunComponent& other) = delete;
			StunComponent(StunComponent&& other) = delete;
			StunComponent& operator=(const StunComponent& other) = delete;
			StunComponent& operator=(StunComponent&& other) = delete;

			virtual void Update() override {};
			virtual void FixedUpdate() override {}

			void StunEnemies(glm::vec2 direction);
	};
}



