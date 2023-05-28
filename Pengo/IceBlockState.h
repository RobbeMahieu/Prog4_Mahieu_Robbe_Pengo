#pragma once
#include <glm/glm.hpp>

namespace dae {
	class GameObject;
}

class CollisionComponent;

class IceBlockState
{
	public:
		IceBlockState(dae::GameObject* m_pOwner);
		virtual ~IceBlockState() = default;
		virtual IceBlockState* Update(float elapsedSec) = 0;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) = 0;

	protected:
		dae::GameObject* m_pOwner;
};

class Sliding final : public IceBlockState {
	
	public:
		Sliding(dae::GameObject* owner, float speed, const glm::vec2& direction);
		virtual ~Sliding() = default;
		virtual IceBlockState* Update(float elapsedSec) override;
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override;

	private:
		float m_SlidingSpeed;
		glm::vec2 m_Direction;
};

class Idle final : public IceBlockState {

	public:
		Idle(dae::GameObject* owner, float speed);
		virtual ~Idle() = default;
		IceBlockState* Update(float /*elapsedSec*/) override { return nullptr; }
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override;

	private:
		float m_Speed;
};

class Break final : public IceBlockState {

	public:
		Break(dae::GameObject* owner);
		virtual ~Break() = default;
		IceBlockState* Update(float /*elapsedSec*/) override { return nullptr; }
		virtual IceBlockState* HandleCollision(CollisionComponent* collider) override { return nullptr; }
};

