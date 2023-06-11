#pragma once
#include "GameState.h"
#include <string>

namespace pengo {

	class EndScreen : public GameState
	{
		public:
			EndScreen(engine::GameObject* pOwner, bool didWin, GameMode mode);
			virtual ~EndScreen() = default;
			virtual void OnEnter() override;
			virtual void OnLeave() override;
			virtual GameState* Update() override;

		private:
			GameMode m_GameMode;
			bool m_DidWin;

			engine::GameObject* m_pScreen;
			engine::GameObject* m_pCursor;
			std::vector<engine::GameObject*> m_pButtons;

			std::vector<std::string> m_HighScores;

			void LoadHighscores();
			void SaveHighscores();
	};
}
