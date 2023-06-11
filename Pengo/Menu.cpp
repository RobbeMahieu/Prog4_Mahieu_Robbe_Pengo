#include "Menu.h"
#include "Playing.h"
#include <TextureRenderComponent.h>
#include <TextRenderComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "MenuInteractor.h"

using namespace pengo;

Menu::Menu(engine::GameObject* pOwner)
	: GameState(pOwner)
	, m_pMenu{ nullptr }
	, m_pCursor{ nullptr }
{
}

Menu::~Menu() {
	m_pMenu->Destroy();
}

void Menu::OnEnter() {
	// Create menu
	m_pMenu = new engine::GameObject();
	m_pMenu->AttachTo(m_pOwner, false);

	// Background
	m_pMenu->AddComponent<engine::TextureRenderComponent>("Backgrounds/menu.png");

	// Buttons
	auto buttonFont = engine::ResourceManager::GetInstance().LoadFont("Arcade.otf", 25);

	engine::GameObject* button = new engine::GameObject();
	button->SetLocalPosition(120, 280);
	button->AddComponent<engine::TextRenderComponent>("1 PLAYER", buttonFont);
	button->AttachTo(m_pMenu, true);
	m_pButtons.push_back(button);

	button = new engine::GameObject();
	button->SetLocalPosition(120, 330);
	button->AddComponent<engine::TextRenderComponent>("2P VS", buttonFont);
	button->AttachTo(m_pMenu, true);
	m_pButtons.push_back(button);

	button = new engine::GameObject();
	button->SetLocalPosition(120, 380);
	button->AddComponent<engine::TextRenderComponent>("2P CO-OP", buttonFont);
	button->AttachTo(m_pMenu, true);
	m_pButtons.push_back(button);

	// Cursor
	m_pCursor = new engine::GameObject();
	m_pCursor->SetLocalPosition(-45, -5);
	m_pCursor->AddComponent<engine::TextureRenderComponent>("Sprites/pengo.png");
	m_pCursor->AttachTo(m_pButtons[0], false);

	// Input
	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	for (engine::InputDevice* device : devices) {

		engine::Keyboard* keyboard{ dynamic_cast<engine::Keyboard*>(device) };
		if (keyboard) {
			m_pMenu->AddComponent<MenuInteractor>(int(m_pButtons.size()), keyboard);
			continue;
		}

		engine::XBoxController* controller{ dynamic_cast<engine::XBoxController*>(device) };
		if (controller) {
			m_pMenu->AddComponent<MenuInteractor>(int(m_pButtons.size()), controller);
			continue;
		}
	}
}

GameState* Menu::Update() {

	// Get selected index
	int index{ MenuInteractor::GetSelectedIndex() };

	// Updated selected item
	if (m_pCursor->GetParent() != m_pButtons[index]) {
		m_pCursor->AttachTo(m_pButtons[index], false);
	}

	if (MenuInteractor::GetOptionChosen()) {
		return new Playing(m_pOwner, GameMode(index));
	}

	return nullptr;
}