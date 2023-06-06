#pragma once
#include <functional>

namespace engine {

	class Command final
	{
	public:
		explicit Command(const std::function<void()>& function);

		~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		void Execute();

	private:
		std::function<void(void)> m_Function;
	};
}