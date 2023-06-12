#pragma once
#include <Component.h>
#include <vector>
#include <GameObject.h>
#include <random>
#include <SubjectObserver.h>

namespace pengo {
	
	class DiamondSpawner final : public engine::Component
	{
		public:
			DiamondSpawner(engine::GameObject* pOwner);
			virtual ~DiamondSpawner() = default;

			DiamondSpawner(const DiamondSpawner& other) = delete;
			DiamondSpawner(DiamondSpawner&& other) = delete;
			DiamondSpawner& operator=(const DiamondSpawner& other) = delete;
			DiamondSpawner& operator=(DiamondSpawner&& other) = delete;

			virtual void Update() override;
			virtual void FixedUpdate() override {}

			void PickDiamondLocations(std::vector<engine::GameObject*> locations, int amount);

			engine::Subject<DiamondSpawner*> m_DiamondsAlligned;

		private:
			std::vector<engine::GameObject*> m_pDiamonds;

			// Random engine
			std::default_random_engine m_RandomEngine;
			bool m_BonusAwarded;
	};
}