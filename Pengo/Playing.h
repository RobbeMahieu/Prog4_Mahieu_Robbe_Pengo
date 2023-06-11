#pragma once
#include "GameState.h"
#include <SubjectObserver.h>

namespace pengo {

	class LevelLoader;
	class EnemySpawner;
	class DiamondSpawner;
	class HealthComponent;

	class Playing final : public GameState, engine::Observer<>, engine::Observer<HealthComponent*, int>
	{
		public:
			Playing(engine::GameObject* pOwner);
			virtual ~Playing() = default;
			virtual void OnEnter() override;
			virtual GameState* Update() override;

			virtual void OnNotify() override;
			virtual void OnNotify(HealthComponent* component, int health) override;

		private:
			engine::GameObject* m_pGame;
			engine::GameObject* m_pLevel;

			bool m_IsPlaying;
			bool m_WonLevel;

			LevelLoader* m_pLevelLoader;
			EnemySpawner* m_pEnemySpawner;
			DiamondSpawner* m_pDiamondSpawner;
			std::vector<engine::GameObject*> m_pPlayers;

			int m_LevelIndex;

			void NextLevel();
			void RestartLevel();
	};

}