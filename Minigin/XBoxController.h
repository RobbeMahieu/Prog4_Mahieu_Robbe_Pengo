#pragma once
#include "InputDevice.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

class XBoxController final : public InputDevice
{
	public:
		XBoxController(int controllerIndex);
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

