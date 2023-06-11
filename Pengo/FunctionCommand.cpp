#include "FunctionCommand.h"

using namespace pengo;

FunctionCommand::FunctionCommand(std::function<void()> function)
	: Command()
	, m_Function{ function }
{
}

void FunctionCommand::Execute() {
	m_Function();
}