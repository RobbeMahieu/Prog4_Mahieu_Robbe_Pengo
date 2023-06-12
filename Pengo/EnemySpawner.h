#pragma once
#include <Component.h>
#include <vector>
#include <GameObject.h>
#include <random>
#include <SubjectObserver.h>

namespace pengo {

	class AIMovement;
	class SlidingComponent;

	class EnemySpawner final : public engine::Component, engine::Observer<engine::GameObject*>, engine::Observer<SlidingComponent*>
	{
		public:
			EnemySpawner(engine::GameObject* pOwner);
			virtual ~EnemySpawner() = default;

			EnemySpawner(const EnemySpawner& other) = delete;
			EnemySpawner(EnemySpawner&& other) = delete;
			EnemySpawner& operator=(const EnemySpawner& other) = delete;
			EnemySpawner& operator=(EnemySpawner&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {}
			
			void PickEnemyLocations(std::vector<engine::GameObject*> locations, int amount);
			void SpawnEnemy();
			void AddPlayerEnemy(engine::GameObject* player);

			virtual void OnNotify(engine::GameObject* object) override;
			virtual void OnNotify(SlidingComponent* object) override;

			std::vector<engine::GameObject*> GetEnemies() const;

			engine::Subject<> m_EnemiesKilled;

		private:
			std::vector<engine::GameObject*> m_SpawnLocations;
			std::vector<engine::GameObject*> m_ActiveEnemies;

			// Random engine
			std::default_random_engine m_RandomEngine;

			int m_EnemyCounter;
			float m_MaxActiveEnemies;
	};

}


