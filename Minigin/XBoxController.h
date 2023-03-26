#pragma once
#include "InputDevice.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>


// Old school enum so they are automatically converted to int when applicable
enum ControllerButton {
	DPAD_UP			= 0x0001,
	DPAD_DOWN		= 0x0002,
	DPAD_LEFT		= 0x0004,
	DPAD_RIGHT		= 0x0008,
	BUTTON_START	= 0x0010,
	BUTTON_BACK		= 0x0020,
	LEFT_THUMB		= 0x0040,
	RIGHT_THUMB		= 0x0080,
	LEFT_SHOULDER	= 0x0100,
	RIGHT_SHOULDER	= 0x0200,
	BUTTON_A		= 0x1000,
	BUTTON_B		= 0x2000,
	BUTTON_X		= 0x4000,
	BUTTON_Y		= 0x8000,

};

class XBoxController final : public InputDevice
{
	public:
		XBoxController(int deviceID, int controllerIndex);
		~XBoxController() = default;

		XBoxController(const XBoxController& other) = delete;
		XBoxController(XBoxController&& other) = delete;
		XBoxController& operator=(const XBoxController& other) = delete;
		XBoxController& operator=(XBoxController&& other) = delete;

		void Update() override;
		bool IsPressed(unsigned int key) const override;
		bool IsPressedThisFrame(unsigned int key) const override;
		bool IsReleasedThisFrame(unsigned int key) const override;

	private:
		int m_ControllerIndex;

		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;

		WORD m_ButtonsPressedThisFrame{};
		WORD m_ButtonsReleasedThisFrame{};
};

