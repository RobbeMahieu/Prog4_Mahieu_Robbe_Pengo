#include "MenuInteractor.h"
#include <InputManager.h>

using namespace pengo;

int MenuInteractor::m_MaxIndex{ 0 };
int MenuInteractor::m_SelectedIndex{ 0 };
bool MenuInteractor::m_OptionChosen{ false };

MenuInteractor::MenuInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device)
	: MenuInteractor(pOwner ,maxIndex)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, m_pNavigateUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, m_pNavigateDown.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuInteractor::MenuInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device)
	: MenuInteractor(pOwner, maxIndex)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, m_pNavigateUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, m_pNavigateDown.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuInteractor::MenuInteractor(engine::GameObject* pOwner, int maxIndex)
	: Component(pOwner)
	, m_pNavigateUp{ std::make_unique<FunctionCommand>(std::bind(&MenuInteractor::ChangeIndex, this, -1)) }
	, m_pNavigateDown{ std::make_unique<FunctionCommand>(std::bind(&MenuInteractor::ChangeIndex, this, 1)) }
	, m_pSelect{ std::make_unique<FunctionCommand>(std::bind(&MenuInteractor::Select, this)) }
{
	m_MaxIndex = maxIndex;
}

MenuInteractor::~MenuInteractor() {
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateUp.get());
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateDown.get());
	engine::InputManager::GetInstance().UnbindAction(m_pSelect.get());
}

void MenuInteractor::ChangeIndex(int amount) {

	if (m_OptionChosen) { return; }

	m_SelectedIndex += amount;

	// Keep index in range
	if (m_SelectedIndex < 0) {
		m_SelectedIndex = m_MaxIndex + m_SelectedIndex;
	}

	m_SelectedIndex %= m_MaxIndex;
}

void MenuInteractor::Select() {
	m_OptionChosen = true;
}

int MenuInteractor::GetSelectedIndex() {
	return m_SelectedIndex;
}

bool MenuInteractor::GetOptionChosen() {
	return m_OptionChosen;
}