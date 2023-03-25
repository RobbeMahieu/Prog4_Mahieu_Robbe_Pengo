#include "Keyboard.h"
#include <SDL.h>

Keyboard::Keyboard() {

	m_CurrentState = SDL_GetKeyboardState(&m_KeysLength);
	m_PreviousState = new Uint8[m_KeysLength]{};
};

Keyboard::~Keyboard() {
	delete[] m_PreviousState;
}

void Keyboard::Update() {
	SDL_memcpy(m_PreviousState, m_CurrentState, m_KeysLength);
}

bool Keyboard::IsPressed(unsigned int key) const {
	return m_CurrentState[key];
}

bool Keyboard::IsPressedThisFrame(unsigned int key) const {
	return !m_PreviousState[key] && m_CurrentState[key];
}

bool Keyboard::IsReleasedThisFrame(unsigned int key) const {
	return m_PreviousState[key] && !m_CurrentState[key];
}