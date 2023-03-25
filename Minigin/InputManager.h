#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	private:


	};

}
