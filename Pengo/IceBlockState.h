#pragma once
#include <glm/glm.hpp>
#include <SubjectObserver.h>

namespace pengo {

	class CollisionComponent;
	class EnemySpawner;
	class SlidingComponent;

	class IceBlockState
	{
	public:
		IceBlockState(SlidingComponent* component);
		virtual ~IceBlockState() = default;
		virtual void OnEnter() = 0;
		virtual IceBlockState* Update() = 0;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) = 0;
		virtual IceBlockState* Push(glm::vec2 direction) = 0;

	protected:
		SlidingComponent* m_pIce;
	};

	class Sliding final : public IceBlockState {

	public:
		Sliding(SlidingComponent* component, const glm::vec2& direction);
		virtual ~Sliding() = default;
		virtual void OnEnter() override;
		virtual IceBlockState* Update() override;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override;
		virtual IceBlockState* Push(glm::vec2 /*direction*/) override{ return nullptr; }

	private:
		glm::vec2 m_Direction;
	};

	class Idle final : public IceBlockState {

	public:
		Idle(SlidingComponent* component);
		virtual ~Idle() = default;
		virtual void OnEnter() override;
		virtual IceBlockState* Update() override { return nullptr; }
		virtual IceBlockState* HandleCollision(CollisionComponent* /*collider*/) override { return nullptr; }
		virtual IceBlockState* Push(glm::vec2 direction) override;

	};

	class Break final : public IceBlockState {

	public:
		Break(SlidingComponent* component);
		virtual ~Break() = default;
		virtual void OnEnter() override {};
		virtual IceBlockState* Update() override;
		virtual IceBlockState* HandleCollision(CollisionComponent* /*collider*/) override { return nullptr; }
		virtual IceBlockState* Push(glm::vec2 /*direction*/) override { return nullptr; }

	};

}

