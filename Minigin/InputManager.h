#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

class Command;
class InputDevice;

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	private:
		std::vector<std::unique_ptr<InputDevice>> m_InputDevices;
	};

}
