#pragma once
namespace engine {

	class InputDevice
	{
		public:
			InputDevice(int deviceID)
				: m_DeviceID{ deviceID }
			{}

			virtual ~InputDevice() = default;

			InputDevice(const InputDevice& other) = delete;
			InputDevice(InputDevice&& other) = delete;
			InputDevice& operator=(const InputDevice& other) = delete;
			InputDevice& operator=(InputDevice&& other) = delete;

			virtual void Update() = 0;
			virtual bool IsPressed(unsigned int key) const = 0;
			virtual bool IsPressedThisFrame(unsigned int key) const = 0;
			virtual bool IsReleasedThisFrame(unsigned int key) const = 0;

			int GetID() { return m_DeviceID; }

		private:
			int m_DeviceID;
	};
}

