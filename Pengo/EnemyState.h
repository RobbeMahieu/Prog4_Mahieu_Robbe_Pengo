#pragma once

namespace pengo {

	class CollisionComponent;
	class MoveCommand;
	class AIMovement;

	class EnemyState
	{
		public:
			EnemyState(AIMovement* pMovement);
			virtual ~EnemyState() = default;
			virtual void OnEnter() = 0;
			virtual EnemyState* Update() = 0;
			virtual EnemyState* HandleCollision(CollisionComponent* collider) = 0;
			virtual EnemyState* Stun() = 0;

		protected:
			AIMovement* m_pMovement;
	};

	class Moving final : public EnemyState {
		public:
			Moving(AIMovement* pMovement);
			virtual ~Moving() = default;
			virtual void OnEnter() override;
			virtual EnemyState* Update() override;
			virtual EnemyState* HandleCollision(CollisionComponent* collider) override;
			virtual EnemyState* Stun();

		private:
			int m_DirectionCount;
	};

	class Turning final : public EnemyState {
		public:
			Turning(AIMovement* pMovement);
			virtual ~Turning() = default;
			virtual void OnEnter() override;
			virtual EnemyState* Update() override;
			virtual EnemyState* HandleCollision(CollisionComponent* /*collider*/) override { return nullptr; };
			virtual EnemyState* Stun();
	};

	class Stunned final : public EnemyState {
		public:
			Stunned(AIMovement* pMovement);
			virtual ~Stunned() = default;
			virtual void OnEnter() override;
			virtual EnemyState* Update() override;
			virtual EnemyState* HandleCollision(CollisionComponent* collider) override;
			virtual EnemyState* Stun();

		private:
			float m_StunTime;
			float m_AccuTime;
	};
}


