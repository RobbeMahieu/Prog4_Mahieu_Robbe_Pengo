#pragma once
#include "GameState.h"
#include <SubjectObserver.h>
#include <chrono>
#include <memory>

namespace pengo {

	class LevelLoader;
	class EnemySpawner;
	class DiamondSpawner;
	class HealthComponent;
	class FunctionCommand;

	class Playing final : public GameState, engine::Observer<>, engine::Observer<HealthComponent*, int>
	{
		public:
			Playing(engine::GameObject* pOwner, GameMode mode);
			virtual ~Playing() = default;
			virtual void OnEnter() override;
			virtual void OnLeave();
			virtual GameState* Update() override;

			virtual void OnNotify() override;
			virtual void OnNotify(HealthComponent* component, int health) override;

		private:
			engine::GameObject* m_pRoot;
			engine::GameObject* m_pGame;
			engine::GameObject* m_pLevel;
			engine::GameObject* m_pHUD;

			bool m_IsPlaying;
			bool m_WonLevel;
			
			// Put in seperate component if time
			std::chrono::steady_clock::time_point m_LevelStartTime;

			LevelLoader* m_pLevelLoader;
			EnemySpawner* m_pEnemySpawner;
			DiamondSpawner* m_pDiamondSpawner;
			std::vector<engine::GameObject*> m_pPlayers;

			GameMode m_GameMode;

			std::unique_ptr<FunctionCommand> m_NextLevelCommand;

			int m_LevelIndex;

			void NextLevel();
			void AddPlayers();
			void CalculateBonus();
			void AddHUD();
			void RestartLevel();
	};

}