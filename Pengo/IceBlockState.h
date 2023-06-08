#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"

namespace pengo {

	class CollisionComponent;

	class IceBlockState
	{
	public:
		IceBlockState(engine::GameObject* m_pOwner);
		virtual ~IceBlockState() = default;
		virtual void OnEnter() = 0;
		virtual IceBlockState* Update() = 0;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) = 0;

	protected:
		engine::GameObject* m_pOwner;
	};

	class Sliding final : public IceBlockState {

	public:
		Sliding(engine::GameObject* owner, float speed, const glm::vec2& direction);
		virtual ~Sliding() = default;
		virtual void OnEnter() override;
		virtual IceBlockState* Update() override;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override;

	private:
		float m_SlidingSpeed;
		glm::vec2 m_Direction;
	};

	class Idle final : public IceBlockState {

	public:
		Idle(engine::GameObject* owner, float speed);
		virtual ~Idle() = default;
		virtual void OnEnter() override;
		IceBlockState* Update() override { return nullptr; }
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override;

	private:
		float m_Speed;
	};

	class Break final : public IceBlockState {

	public:
		Break(engine::GameObject* owner);
		virtual ~Break() = default;
		virtual void OnEnter() override {};
		IceBlockState* Update() override { return nullptr; }
		virtual IceBlockState* HandleCollision(CollisionComponent* /*collider*/) override { return nullptr; }
	};

}

