#pragma once
#include "GameState.h"
#include <Observer.h>

namespace pengo {

	class LevelLoader;
	class EnemySpawner;

	class Playing final : public GameState, engine::Observer<>
	{
		public:
			Playing(engine::GameObject* pOwner);
			virtual ~Playing() = default;
			virtual void OnEnter() override;
			virtual GameState* Update() override;

			virtual void OnNotify() override;

		private:
			engine::GameObject* m_pGame;

			bool m_IsPlaying;
			LevelLoader* m_pLevelLoader;
			EnemySpawner* m_pEnemySpawner;
			std::vector<engine::GameObject*> m_pPlayers;
	};

}