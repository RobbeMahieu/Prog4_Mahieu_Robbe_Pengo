#include "XBoxController.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

class XBoxController::XBoxControllerImpl {

	int m_ControllerIndex;

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	public:
		XBoxControllerImpl(int controllerIndex);
		~XBoxControllerImpl() = default;

		XBoxControllerImpl(const XBoxControllerImpl& other) = delete;
		XBoxControllerImpl(XBoxControllerImpl&& other) = delete;
		XBoxControllerImpl& operator=(const XBoxControllerImpl& other) = delete;
		XBoxControllerImpl& operator=(XBoxControllerImpl&& other) = delete;

		void Update();
		bool IsPressed(unsigned int key) const;
		bool IsPressedThisFrame(unsigned int key) const;
		bool IsReleasedThisFrame(unsigned int key) const;
};



// XBoxController

XBoxController::XBoxController(int deviceID, int controllerIndex)
	: InputDevice(deviceID)
{
	pImpl = std::make_unique<XBoxControllerImpl>(controllerIndex);
}

XBoxController::~XBoxController() = default;

void XBoxController::Update() {
	pImpl->Update();
}

bool XBoxController::IsPressed(unsigned int key) const {
	return pImpl->IsPressed(key);
}

bool XBoxController::IsPressedThisFrame(unsigned int key) const {
	return pImpl->IsPressedThisFrame(key);
}

bool XBoxController::IsReleasedThisFrame(unsigned int key) const {
	return pImpl->IsReleasedThisFrame(key);
}



// XboxControllerImpl

XBoxController::XBoxControllerImpl::XBoxControllerImpl(int controllerIndex)
	: m_ControllerIndex{ controllerIndex }
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void XBoxController::XBoxControllerImpl::Update() {
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & ~(m_CurrentState.Gamepad.wButtons);
}

bool XBoxController::XBoxControllerImpl::IsPressed(unsigned int key) const {
	return m_CurrentState.Gamepad.wButtons & key;
}

bool XBoxController::XBoxControllerImpl::IsPressedThisFrame(unsigned int key) const {
	return m_ButtonsPressedThisFrame & key;
}

bool XBoxController::XBoxControllerImpl::IsReleasedThisFrame(unsigned int key) const {
	return m_ButtonsReleasedThisFrame & key;
}