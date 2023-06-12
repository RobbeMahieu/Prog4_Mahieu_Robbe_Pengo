#include "GameManager.h"
#include "GameState.h"
#include "Menu.h"
#include "Playing.h"
#include "FunctionCommand.h"
#include <GameServiceLocator.h>
#include <functional>
#include <InputManager.h>
#include <Keyboard.h>
#include <XBoxController.h>

using namespace pengo;

GameManager::GameManager(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_pState{ new Menu(pOwner) }
	, m_MusicStarted{ false }
	, m_IsMuted{ false }
	, m_ToggeSound{std::make_unique<FunctionCommand>(std::bind(&GameManager::ToggleSound, this))}
{
	m_pState->OnEnter();

	// Input
	std::vector<engine::InputDevice*> devices{ engine::InputManager::GetInstance().GetInputDevices() };
	for (engine::InputDevice* device : devices) {
		engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_M, m_ToggeSound.get(), device->GetID(), engine::KeyState::OnPress);
	}
}

GameManager::~GameManager() {

	engine::InputManager::GetInstance().UnbindAction(m_ToggeSound.get());

	delete m_pState;
}

void GameManager::Update() {

	if (!m_MusicStarted) {
		// Start music
		engine::GameServiceLocator::GetSoundSystem().PlayMusic("../Data/Sounds/popcorn.mp3", 0.3f);
		m_MusicStarted = true;
	}

	auto state = m_pState->Update();
	TransitionTo(state);
}


void GameManager::TransitionTo(GameState* state) {
	if (state && state != m_pState) {
		m_pState->OnLeave();
		delete m_pState;
		m_pState = state;
		m_pState->OnEnter();
	}
}

void GameManager::ToggleSound() {
	m_IsMuted = !m_IsMuted;

	engine::GameServiceLocator::GetSoundSystem().SetMute(m_IsMuted);
}