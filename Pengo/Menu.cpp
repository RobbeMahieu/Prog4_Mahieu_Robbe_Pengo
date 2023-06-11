#include "Menu.h"
#include "Playing.h"

using namespace pengo;

Menu::Menu(engine::GameObject* pOwner)
	: GameState(pOwner)
{
}

GameState* Menu::Update() {
	return new Playing(m_pOwner);
}