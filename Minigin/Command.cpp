#include "Command.h"
#include "Component.h"

using namespace engine;

Command::Command(const std::function<void(void)>& function)
	: m_Function{ function }
{
}

void Command::Execute() {
	m_Function();
}