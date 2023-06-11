#pragma once
#include <Component.h>
#include <Keyboard.h>
#include <XBoxController.h>
#include <memory>
#include "FunctionCommand.h"

namespace pengo {
	
	class MenuInteractor : public engine::Component
	{
		public:
			MenuInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device);
			MenuInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device);
			virtual ~MenuInteractor();

			MenuInteractor(const MenuInteractor& other) = delete;
			MenuInteractor(MenuInteractor&& other) = delete;
			MenuInteractor& operator=(const MenuInteractor& other) = delete;
			MenuInteractor& operator=(MenuInteractor&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}
			
			static int GetSelectedIndex();
			static bool GetOptionChosen();

		private:
			MenuInteractor(engine::GameObject* pOwner, int maxIndex);

			std::unique_ptr<FunctionCommand> m_pNavigateUp;
			std::unique_ptr<FunctionCommand> m_pNavigateDown;
			std::unique_ptr<FunctionCommand> m_pSelect;

			static int m_SelectedIndex;
			static int m_MaxIndex;
			static bool m_OptionChosen;

			void ChangeIndex(int amount);
			void Select();
	};
}
