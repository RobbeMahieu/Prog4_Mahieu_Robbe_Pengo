#include "XBoxController.h"

XBoxController::XBoxController(int deviceID, int controllerIndex)
	: InputDevice(deviceID)
	, m_ControllerIndex{ controllerIndex }
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void XBoxController::Update() {
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ~(m_CurrentState.Gamepad.wButtons);
}

bool XBoxController::IsPressed(unsigned int key) const {
	return m_CurrentState.Gamepad.wButtons & key ;
}

bool XBoxController::IsPressedThisFrame(unsigned int key) const {
	return m_ButtonsPressedThisFrame & key;
}

bool XBoxController::IsReleasedThisFrame(unsigned int key) const {
	return m_ButtonsReleasedThisFrame & key;
}