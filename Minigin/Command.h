#pragma once
#include <functional>

namespace dae {
	class GameObject;
}

class Command
{
	public:
		// Member function
		explicit Command(dae::GameObject* pSubject, std::function<void(dae::GameObject*)> function);
		// Global function
		explicit Command(std::function<void(void)> function);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		void Execute();

	private:
		dae::GameObject* m_pSubject;
		std::function<void(dae::GameObject*)> m_MemberFunction;
		std::function<void(void)> m_GlobalFunction;
};

