#include "GameManager.h"
#include "GameState.h"
#include "Menu.h"
#include "Playing.h"
#include <GameServiceLocator.h>

using namespace pengo;

GameManager::GameManager(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_pState{ new Menu(pOwner) }
	, m_MusicStarted{ false }
{
	m_pState->OnEnter();
}

GameManager::~GameManager() {
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