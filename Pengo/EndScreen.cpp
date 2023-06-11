#include "EndScreen.h"
#include <iostream>

using namespace pengo;

EndScreen::EndScreen(engine::GameObject* pOwner, bool didWin)
	: GameState(pOwner)
	, m_DidWin{ didWin }
{

}

void EndScreen::OnEnter() {
	std::cout << (m_DidWin ? "YOU WON!" : "YOU LOSE!");
}