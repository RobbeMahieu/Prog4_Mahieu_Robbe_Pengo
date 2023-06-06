#pragma once
#include "InputDevice.h"
#include <SDL.h>

namespace engine {
	
	class Keyboard final : public InputDevice
	{
		public:
			Keyboard(int deviceID);
			~Keyboard();

			Keyboard(const Keyboard& other) = delete;
			Keyboard(Keyboard&& other) = delete;
			Keyboard& operator=(const Keyboard& other) = delete;
			Keyboard& operator=(Keyboard&& other) = delete;

			void Update() override;
			bool IsPressed(unsigned int key) const override;
			bool IsPressedThisFrame(unsigned int key) const override;
			bool IsReleasedThisFrame(unsigned int key) const override;

		private:
			int m_KeysLength{};
			const Uint8* m_CurrentState;
			Uint8* m_PreviousState;

	};
}



