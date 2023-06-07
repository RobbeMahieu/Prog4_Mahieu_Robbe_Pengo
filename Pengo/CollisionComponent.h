#pragma once
#include <Component.h>
#include "Subject.h"
#include <vector>
#include <unordered_set>

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
			CollisionComponent(engine::GameObject* pOwner, int width, int height, bool trigger = false, PhysicsType type = PhysicsType::STATIC);
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

			engine::Subject<CollisionComponent*> OnCollision;
			engine::Subject<CollisionComponent*> Collides;
			engine::Subject<CollisionComponent*> EndCollision;

		private:
			int m_Width;
			int m_Height;

			bool m_IsTrigger;
			PhysicsType m_Type;

			// Not the best option, but will do for now
			static std::vector<CollisionComponent*> m_pColliders;

			std::unordered_set<CollisionComponent*> m_pColliding;
	};

}
