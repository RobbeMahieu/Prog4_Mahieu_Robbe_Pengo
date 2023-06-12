#pragma once
#include <Component.h>
#include <Keyboard.h>
#include <XBoxController.h>
#include <memory>
#include "FunctionCommand.h"

namespace pengo {

	class MenuHorizontalInteractor final : public engine::Component
	{
	public:
		MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device);
		MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device);
		virtual ~MenuHorizontalInteractor();

		MenuHorizontalInteractor(const MenuHorizontalInteractor& other) = delete;
		MenuHorizontalInteractor(MenuHorizontalInteractor&& other) = delete;
		MenuHorizontalInteractor& operator=(const MenuHorizontalInteractor& other) = delete;
		MenuHorizontalInteractor& operator=(MenuHorizontalInteractor&& other) = delete;

		virtual void Update() override {}
		virtual void FixedUpdate() override {}

		static int GetSelectedIndex();
		static bool GetOptionChosen();

		void Enable(bool enable);

	private:
		bool m_IsEnabled;

		MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex);

		std::unique_ptr<FunctionCommand> m_pNavigateLeft;
		std::unique_ptr<FunctionCommand> m_pNavigateRight;
		std::unique_ptr<FunctionCommand> m_pSelect;

		static int m_SelectedIndex;
		static int m_MaxIndex;
		static bool m_OptionChosen;

		void ChangeIndex(int amount);
		void Select();
	};
}
