#pragma once
class InputDevice
{
	public:
		InputDevice() = default;
		virtual ~InputDevice() = default;

		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

		virtual void Update() = 0;
		virtual bool IsPressed(unsigned int key) const = 0;
		virtual bool IsPressedThisFrame(unsigned int key) const = 0;
		virtual bool IsReleasedThisFrame(unsigned int key) const = 0;
};

