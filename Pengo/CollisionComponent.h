#pragma once
#include <Component.h>
#include "Subject.h"
#include <vector>
#include <unordered_set>

enum class PhysicsType {
	STATIC,
	MOVABLE,
	DYNAMIC
};

// Origin is top left corner

class CollisionComponent : public Component
{
	public:
		CollisionComponent(dae::GameObject* pOwner, int width, int height, bool trigger = false, PhysicsType type = PhysicsType::STATIC);
		virtual ~CollisionComponent();

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		virtual void Update([[maybe_unused]] float elapsedSec) {}
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec);
		virtual void Render() const override;

		const std::unordered_set<CollisionComponent*> GetColliding() const;
		PhysicsType GetType() const;

		Subject<CollisionComponent*> OnCollision;
		Subject<CollisionComponent*> Collides;
		Subject<CollisionComponent*> EndCollision;

	private:
		int m_Width;
		int m_Height;

		bool m_IsTrigger;
		PhysicsType m_Type;

		// Not the best option, but will do for now
		static std::vector<CollisionComponent*> m_pColliders;

		std::unordered_set<CollisionComponent*> m_pColliding;
};


