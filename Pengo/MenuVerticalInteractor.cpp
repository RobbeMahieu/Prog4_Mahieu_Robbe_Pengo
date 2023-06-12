#include "MenuVerticalInteractor.h"
#include <InputManager.h>

using namespace pengo;

int MenuVerticalInteractor::m_MaxIndex{ 0 };
int MenuVerticalInteractor::m_SelectedIndex{ 0 };
bool MenuVerticalInteractor::m_OptionChosen{ false };

MenuVerticalInteractor::MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device)
	: MenuVerticalInteractor(pOwner ,maxIndex)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, m_pNavigateUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, m_pNavigateDown.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuVerticalInteractor::MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device)
	: MenuVerticalInteractor(pOwner, maxIndex)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, m_pNavigateUp.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, m_pNavigateDown.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuVerticalInteractor::MenuVerticalInteractor(engine::GameObject* pOwner, int maxIndex)
	: Component(pOwner)
	, m_pNavigateUp{ std::make_unique<FunctionCommand>(std::bind(&MenuVerticalInteractor::ChangeIndex, this, -1)) }
	, m_pNavigateDown{ std::make_unique<FunctionCommand>(std::bind(&MenuVerticalInteractor::ChangeIndex, this, 1)) }
	, m_pSelect{ std::make_unique<FunctionCommand>(std::bind(&MenuVerticalInteractor::Select, this)) }
	, m_IsEnabled{ true }
{
	m_MaxIndex = maxIndex;
	m_OptionChosen = false;
	m_SelectedIndex = 0;
}

MenuVerticalInteractor::~MenuVerticalInteractor() {
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateUp.get());
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateDown.get());
	engine::InputManager::GetInstance().UnbindAction(m_pSelect.get());
}

void MenuVerticalInteractor::ChangeIndex(int amount) {

	if (m_OptionChosen ||!m_IsEnabled) { return; }

	m_SelectedIndex += amount;

	// Keep index in range
	if (m_SelectedIndex < 0) {
		m_SelectedIndex = m_MaxIndex + m_SelectedIndex;
	}

	m_SelectedIndex %= m_MaxIndex;
}

void MenuVerticalInteractor::Select() {
	m_OptionChosen = true;
}

int MenuVerticalInteractor::GetSelectedIndex() {
	return m_SelectedIndex;
}

bool MenuVerticalInteractor::GetOptionChosen() {
	return m_OptionChosen;
}

void MenuVerticalInteractor::Enable(bool enable) {
	m_IsEnabled = enable;
}