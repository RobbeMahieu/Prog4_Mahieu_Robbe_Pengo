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

		private:
			int m_DirectionCount;
	};

	class Turning final : public EnemyState {
		public:
			Turning(AIMovement* pMovement);
			virtual ~Turning() = default;
			virtual void OnEnter() override {};
			virtual EnemyState* Update() override;
			virtual EnemyState* HandleCollision(CollisionComponent* collider) override;
	};

	class Stuck final : public EnemyState {
		public:
			Stuck(AIMovement* pMovement);
			virtual ~Stuck() = default;
			virtual void OnEnter() override {};
			virtual EnemyState* Update() override { return nullptr; };
			virtual EnemyState* HandleCollision(CollisionComponent* collider) override;
	};

	class Die final : public EnemyState {

	public:
		Die(AIMovement* pMovement);
		virtual ~Die() = default;
		virtual void OnEnter() override {};
		virtual EnemyState* Update() override { return nullptr; }
		virtual EnemyState* HandleCollision(CollisionComponent* /*collider*/) override { return nullptr; }
	};
}


