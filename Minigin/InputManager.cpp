#include "InputManager.h"
#include "SDL.h"

using namespace engine;

bool InputManager::ProcessInput()
{
	// Update key presses for each input device
	for (auto& inputDevice : m_InputDevices) {
		inputDevice->Update();
	}

	// Handle SDL events
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	// Check action mappings
	for (const auto& actionMap : m_ActionMapping) {

		switch (actionMap.keystate) {
			case KeyState::OnPress:
				if (m_InputDevices[actionMap.deviceIndex]->IsPressedThisFrame(actionMap.key)) {
					actionMap.command->Execute();
				}
				break;

			case KeyState::OnRelease:
				if (m_InputDevices[actionMap.deviceIndex]->IsReleasedThisFrame(actionMap.key)) {
					actionMap.command->Execute();
				}
				break;

			case KeyState::Pressed:
				if (m_InputDevices[actionMap.deviceIndex]->IsPressed(actionMap.key)) {
					actionMap.command->Execute();
				}
				break;

			case KeyState::Released:
				if (!m_InputDevices[actionMap.deviceIndex]->IsPressed(actionMap.key)) {
					actionMap.command->Execute();
				}
				break;
		}

	}

	return true;
}

void InputManager::BindAction(unsigned int key, Command* pCommand, int deviceIndex, KeyState state) {
	
	m_ActionMapping.push_back(ActionMap{ pCommand, key, deviceIndex, state });
}

void InputManager::UnbindAction(Command* pCommand) {
	m_ActionMapping.erase(std::remove_if(m_ActionMapping.begin(), m_ActionMapping.end(), [&](const ActionMap& action) {

		return action.command == pCommand;

	}), m_ActionMapping.end());
}
