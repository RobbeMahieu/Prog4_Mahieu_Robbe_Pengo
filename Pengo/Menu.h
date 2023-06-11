#pragma once
#include "GameState.h"
#include <vector>
#include <GameObject.h>
#include "FunctionCommand.h"
#include <memory>

namespace pengo{

	class Menu : public GameState
	{
		public:
			Menu(engine::GameObject* pOwner);
			virtual ~Menu();
			virtual void OnEnter() override;
			virtual GameState* Update() override;

		private:
			engine::GameObject* m_pMenu;
			engine::GameObject* m_pCursor;
			std::vector<engine::GameObject*> m_pButtons;

			GameState* Select(int index);
	};

}