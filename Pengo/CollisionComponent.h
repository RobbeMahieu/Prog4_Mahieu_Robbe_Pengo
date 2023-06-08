#pragma once
#include <Component.h>
#include "Subject.h"
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>

namespace pengo {

	enum class PhysicsType {
		STATIC,
		MOVABLE,
		DYNAMIC
	};

	// Origin is top left corner

	class CollisionComponent : public engine::Component
	{
		public:
			CollisionComponent(engine::GameObject* pOwner, float width, float height, bool trigger = false, PhysicsType type = PhysicsType::STATIC);
			virtual ~CollisionComponent();

			CollisionComponent(const CollisionComponent& other) = delete;
			CollisionComponent(CollisionComponent&& other) = delete;
			CollisionComponent& operator=(const CollisionComponent& other) = delete;
			CollisionComponent& operator=(CollisionComponent&& other) = delete;

			virtual void Update() override{}
			virtual void FixedUpdate() override;
			virtual void Render() const override;

			const std::unordered_set<CollisionComponent*> GetColliding() const;
			PhysicsType GetType() const;
			void SetType(PhysicsType type);

			// Returns x, y, width, height
			glm::vec4 GetBounds() const;

			engine::Subject<CollisionComponent*> OnCollision;
			engine::Subject<CollisionComponent*> Collides;
			engine::Subject<CollisionComponent*> EndCollision;

			static bool CheckCollision(float x, float y, float width, float height, std::vector<CollisionComponent*> toIgnore = {});
			static bool CheckCollision(glm::vec4 bounds, std::vector<CollisionComponent*> toIgnore = {});
			static bool CheckCollision(CollisionComponent* collider, std::vector<CollisionComponent*> toIgnore = {});

		private:
			float m_Width;
			float m_Height;

			bool m_IsTrigger;
			PhysicsType m_Type;

			// Not the best option, but will do for now
			static std::vector<CollisionComponent*> m_pColliders;

			std::unordered_set<CollisionComponent*> m_pColliding;
	};

}
