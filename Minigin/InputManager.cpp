#include <SDL.h>
#include "InputManager.h"
#include <iostream>

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
	}

	// Update key presses for each input device
	for (auto& inputDevice : m_InputDevices) {
		inputDevice->Update();
	}

	// Check action mappings
	for (const auto& actionMap : m_ActionMapping) {
		if (m_InputDevices[actionMap.deviceIndex]->IsPressed(actionMap.key)) {
			actionMap.command->Execute();
		}
	}

	return true;
}

void dae::InputManager::AddInputDevice(InputDevice* pDevice) {

	std::unique_ptr<InputDevice> device{ pDevice };
	m_InputDevices.push_back(std::move(device));
}

void dae::InputManager::BindAction(unsigned int key, Command* pCommand, int deviceIndex) {
	
	std::unique_ptr<Command> command{ pCommand };
	m_ActionMapping.push_back(ActionMap{ std::move(command), key, deviceIndex });
}
