#pragma once
#include <Component.h>
#include <vector>
#include <GameObject.h>
#include <random>

namespace pengo {

	class EnemySpawner : public engine::Component
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

		private:
			std::vector<engine::GameObject*> m_SpawnLocations;

			// Random engine
			std::default_random_engine m_RandomEngine;
			int m_EnemyCounter;
	};

}

