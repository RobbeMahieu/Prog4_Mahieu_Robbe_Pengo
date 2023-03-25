#include <SDL.h>
#include "InputManager.h"
#include "InputDevice.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	// Update key presses for each input device
	for (auto& inputDevice : m_InputDevices) {
		inputDevice->Update();
	}

	return true;
}
