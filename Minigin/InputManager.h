#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "InputDevice.h"
#include "Command.h"

namespace engine {

	enum class KeyState {
		OnPress,
		OnRelease,
		Pressed,
		Released
	};

	struct ActionMap {
		std::unique_ptr<Command> command;
		unsigned int key;
		int deviceIndex;
		KeyState keystate;
	};


	class InputManager final : public Singleton<InputManager>
	{
		public:
			bool ProcessInput();

			template<typename DeviceType, typename... Args>
			DeviceType* AddInputDevice(Args&&... arguments) {
				std::unique_ptr<DeviceType> device{ std::make_unique<DeviceType>(int(m_InputDevices.size()), std::forward<Args>(arguments)...) };
				m_InputDevices.push_back(std::move(device));
				return static_cast<DeviceType*>(m_InputDevices.back().get());
			}

			void BindAction(unsigned int key, Command* pCommand, int deviceIndex = 0, KeyState state = KeyState::Pressed);

		private:
			std::vector<std::unique_ptr<InputDevice>> m_InputDevices;
			std::vector<ActionMap> m_ActionMapping;

	};	
}
