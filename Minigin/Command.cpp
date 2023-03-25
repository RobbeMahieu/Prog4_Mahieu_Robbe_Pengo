#include "Command.h"
#include "Component.h"

Command::Command(std::function<void(void)> function)
	: m_Function{ function }
{
}

void Command::Execute() {

	m_Function();
}