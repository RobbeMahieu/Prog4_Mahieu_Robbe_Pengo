#pragma once
#include <Component.h>
#include <Keyboard.h>
#include <XBoxController.h>
#include <memory>
#include "FunctionCommand.h"

namespace pengo {
	
	class MenuVerticalInteractor : public engine::Component
	{
		public:
			MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device);
			MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device);
			virtual ~MenuVerticalInteractor();

			MenuVerticalInteractor(const MenuVerticalInteractor& other) = delete;
			MenuVerticalInteractor(MenuVerticalInteractor&& other) = delete;
			MenuVerticalInteractor& operator=(const MenuVerticalInteractor& other) = delete;
			MenuVerticalInteractor& operator=(MenuVerticalInteractor&& other) = delete;

			virtual void Update() override {}
			virtual void FixedUpdate() override {}
			
			static int GetSelectedIndex();
			static bool GetOptionChosen();

			void Enable(bool enable);

		private:
			bool m_IsEnabled;

			MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex);

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
