#pragma once
#include "GameState.h"

namespace pengo{

	class Menu : public GameState
	{
		public:
			Menu(engine::GameObject* pOwner);
			virtual ~Menu() = default;
			virtual void OnEnter() override {};
			virtual GameState* Update() override;

		private:


	};

}