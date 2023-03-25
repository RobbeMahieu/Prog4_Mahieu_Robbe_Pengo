#include "Command.h"
#include "GameObject.h"

Command::Command(dae::GameObject* pSubject, std::function<void(dae::GameObject*)> function)
	: m_pSubject{ pSubject }
	, m_MemberFunction{ function }
	, m_GlobalFunction{ nullptr }
{
}

Command::Command(std::function<void(void)> function)
	: m_pSubject{ nullptr }
	, m_MemberFunction{ nullptr }
	, m_GlobalFunction{ function }
{
}

void Command::Execute() {

	if (m_pSubject) {
		m_MemberFunction(m_pSubject);
	}
	else {
		m_GlobalFunction();
	}
}