#pragma once
#include <Component.h>
#include "Subject.h"
#include <vector>
#include <unordered_set>


// Origin is top left corner

class CollisionComponent : public Component
{
	public:
		CollisionComponent(dae::GameObject* pOwner, float width, float height, bool solid = true, bool movable = true);
		virtual ~CollisionComponent();

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		virtual void Update([[maybe_unused]] float elapsedSec) {}
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec);
		virtual void Render() const override;

		const std::unordered_set<CollisionComponent*> GetColliding() const;

		Subject<CollisionComponent*> OnCollision;
		Subject<CollisionComponent*> Collides;
		Subject<CollisionComponent*> EndCollision;

	private:
		float m_Width;
		float m_Height;

		bool m_IsSolid;
		bool m_IsMovable;

		// Not the best option, but will do for now
		static std::vector<CollisionComponent*> m_pColliders;

		std::unordered_set<CollisionComponent*> m_pColliding;
};


