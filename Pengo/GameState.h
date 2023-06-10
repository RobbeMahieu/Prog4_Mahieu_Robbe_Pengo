#pragma once
#include <GameObject.h>

namespace pengo {
	
	class GameState
	{
		public:
			GameState(engine::GameObject* pOwner);
			virtual ~GameState() = default;
			virtual void OnEnter() = 0;
			virtual GameState* Update() = 0;

		protected:
			engine::GameObject* m_pOwner;
	};

}