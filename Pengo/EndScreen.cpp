#include "EndScreen.h"
#include <iostream>
#include <TextureRenderComponent.h>
#include <TextRenderComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "MenuInteractor.h"
#include "Playing.h"
#include "Menu.h"

using namespace pengo;

EndScreen::EndScreen(engine::GameObject* pOwner, bool didWin, GameMode mode)
	: GameState(pOwner)
	, m_DidWin{ didWin }
	, m_pScreen{ nullptr }
	, m_pCursor{ nullptr }
	, m_GameMode{ mode }
{
}

void EndScreen::OnLeave() {
	m_pScreen->Destroy();
}

void EndScreen::OnEnter() {
	std::cout << (m_DidWin ? "YOU WON!" : "YOU LOSE!");

	// Create menu
	m_pScreen = new engine::GameObject();
	m_pScreen->AttachTo(m_pOwner, false);


	// Buttons
	auto buttonFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 25);

	engine::GameObject* button = new engine::GameObject();
	button->SetLocalPosition(120, 330);
	button->AddComponent<engine::TextRenderComponent>("PLAY AGAIN", buttonFont);
	button->AttachTo(m_pScreen, true);
	m_pButtons.push_back(button);

	button = new engine::GameObject();
	button->SetLocalPosition(120, 380);
	button->AddComponent<engine::TextRenderComponent>("MENU", buttonFont);
	button->AttachTo(m_pScreen, true);
	m_pButtons.push_back(button);


	// Cursor
	m_pCursor = new engine::GameObject();
	m_pCursor->SetLocalPosition(-45, -5);
	m_pCursor->AddComponent<engine::TextureRenderComponent>("Sprites/cursor.png");
	m_pCursor->AttachTo(m_pButtons[0], false);

	// Input
	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	for (engine::InputDevice* device : devices) {

		engine::Keyboard* keyboard{ dynamic_cast<engine::Keyboard*>(device) };
		if (keyboard) {
			m_pScreen->AddComponent<MenuInteractor>(int(m_pButtons.size()), keyboard);
			continue;
		}

		engine::XBoxController* controller{ dynamic_cast<engine::XBoxController*>(device) };
		if (controller) {
			m_pScreen->AddComponent<MenuInteractor>(int(m_pButtons.size()), controller);
			continue;
		}
	}
}

GameState* EndScreen::Update() {

	// Get selected index
	int index{ MenuInteractor::GetSelectedIndex() };

	// Updated selected item
	if (m_pCursor->GetParent() != m_pButtons[index]) {
		m_pCursor->AttachTo(m_pButtons[index], false);
	}

	if (MenuInteractor::GetOptionChosen()) {

		if (index == 0) {
			return new Playing(m_pOwner, m_GameMode);
		}
		else {
			return new Menu(m_pOwner);
		}
	}

	return nullptr;
}