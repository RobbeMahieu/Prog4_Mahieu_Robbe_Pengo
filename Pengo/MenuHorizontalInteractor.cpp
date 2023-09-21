#include "MenuHorizontalInteractor.h"
#include <InputManager.h>

using namespace pengo;

int MenuHorizontalInteractor::m_MaxIndex{ 0 };
int MenuHorizontalInteractor::m_SelectedIndex{ 0 };
bool MenuHorizontalInteractor::m_OptionChosen{ false };

MenuHorizontalInteractor::MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex, engine::Keyboard* device)
	: MenuHorizontalInteractor(pOwner, maxIndex)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, m_pNavigateLeft.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, m_pNavigateRight.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuHorizontalInteractor::MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex, engine::XBoxController* device)
	: MenuHorizontalInteractor(pOwner, maxIndex)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_LEFT, m_pNavigateLeft.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_RIGHT, m_pNavigateRight.get(), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_pSelect.get(), device->GetID(), engine::KeyState::OnPress);
}

MenuHorizontalInteractor::MenuHorizontalInteractor(engine::GameObject* pOwner, int maxIndex)
	: Component(pOwner)
	, m_pNavigateLeft{ std::make_unique<FunctionCommand>(std::bind(&MenuHorizontalInteractor::ChangeIndex, this, -1)) }
	, m_pNavigateRight{ std::make_unique<FunctionCommand>(std::bind(&MenuHorizontalInteractor::ChangeIndex, this, 1)) }
	, m_pSelect{ std::make_unique<FunctionCommand>(std::bind(&MenuHorizontalInteractor::Select, this)) }
	, m_IsEnabled{ true }
{
	m_MaxIndex = maxIndex;
	m_OptionChosen = false;
	m_SelectedIndex = 0;
}

MenuHorizontalInteractor::~MenuHorizontalInteractor() {
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateLeft.get());
	engine::InputManager::GetInstance().UnbindAction(m_pNavigateRight.get());
	engine::InputManager::GetInstance().UnbindAction(m_pSelect.get());
}

void MenuHorizontalInteractor::ChangeIndex(int amount) {

	if (m_OptionChosen || !m_IsEnabled) { return; }

	m_SelectedIndex += amount;

	// Keep index in range
	if (m_SelectedIndex < 0) {
		m_SelectedIndex = m_MaxIndex + m_SelectedIndex;
	}

	m_SelectedIndex %= m_MaxIndex;
}

void MenuHorizontalInteractor::Select() {
	m_OptionChosen = true;
}

int MenuHorizontalInteractor::GetSelectedIndex() {
	return m_SelectedIndex;
}

bool MenuHorizontalInteractor::GetOptionChosen() {
	return m_OptionChosen;
}

void MenuHorizontalInteractor::Enable(bool enable) {
	m_IsEnabled = enable;
}