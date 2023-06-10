#include "GameManager.h"
#include "GameState.h"
#include "Playing.h"

using namespace pengo;

GameManager::GameManager(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_pState{ new Playing(pOwner) }
{
	m_pState->OnEnter();
}

GameManager::~GameManager() {
	delete m_pState;
}

void GameManager::Update() {
	auto state = m_pState->Update();
	TransitionTo(state);
}


void GameManager::TransitionTo(GameState* state) {
	if (state && state != m_pState) {
		delete m_pState;
		m_pState = state;
		m_pState->OnEnter();
	}
}