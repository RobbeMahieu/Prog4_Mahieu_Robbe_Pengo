#pragma once
#include <Component.h>
#include <GameObject.h>
#include <SubjectObserver.h>
#include <vector>
#include <unordered_set>
#include <glm/glm.hpp>
#include <chrono>

namespace pengo {

	enum class CollisionLayer {
		STATIC,
		DYNAMIC,
		PLAYER,
		ENEMY,
	};

	class CollisionComponent;

	struct CollisionHit {
		bool hit{ false };
		float distance{};
		glm::vec3 offset{};
		engine::GameObject* object{ nullptr };
		CollisionComponent* collider{ nullptr };
	};

	// Origin is top left corner

	class CollisionComponent : public engine::Component
	{
		public:
			CollisionComponent(engine::GameObject* pOwner, float width, float height, bool trigger = false, CollisionLayer layer = CollisionLayer::STATIC);
			virtual ~CollisionComponent();

			CollisionComponent(const CollisionComponent& other) = delete;
			CollisionComponent(CollisionComponent&& other) = delete;
			CollisionComponent& operator=(const CollisionComponent& other) = delete;
			CollisionComponent& operator=(CollisionComponent&& other) = delete;

			virtual void Update() override{}
			virtual void FixedUpdate() override;
			virtual void Render() const override;

			const std::unordered_set<CollisionComponent*> GetColliding() const;
			const std::unordered_set<CollisionComponent*> GetCollided() const;
			CollisionLayer GetLayer() const;
			void SetLayer(CollisionLayer type);

			// Returns x, y, width, height
			glm::vec4 GetBounds() const;

			engine::Subject<CollisionComponent*> OnCollision;
			engine::Subject<CollisionComponent*> Collides;
			engine::Subject<CollisionComponent*> EndCollision;

			CollisionHit CheckCollision(std::vector<CollisionComponent*> toIgnore = {}, std::vector<CollisionLayer> hitLayers = {});
			std::vector<CollisionHit> GetAllColliding(std::vector<CollisionComponent*> toIgnore = {}, std::vector<CollisionLayer> hitLayers = {});

		private:
			float m_Width;
			float m_Height;

			bool m_IsTrigger;
			CollisionLayer m_Layer;

			std::chrono::steady_clock::time_point m_FrameStart{};

			// Not the best option, but will do for now
			static std::vector<CollisionComponent*> m_pColliders;

			std::unordered_set<CollisionComponent*> m_pColliding{};
			std::unordered_set<CollisionComponent*> m_pCollided{};

			CollisionHit CollidesWith(CollisionComponent* collider);
	};

}
