#pragma once
#include "GameState.h"

namespace pengo {

	class EndScreen : public GameState
	{
		public:
			EndScreen(engine::GameObject* pOwner, bool didWin);
			virtual ~EndScreen() = default;
			virtual void OnEnter() override;
			virtual GameState* Update() override { return nullptr; };

		private:
			bool m_DidWin;
	};
}
