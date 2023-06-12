#include "FunctionCommand.h"

using namespace pengo;

FunctionCommand::FunctionCommand(const std::function<void()>& function)
	: Command()
	, m_Function{ function }
{
}

void FunctionCommand::Execute() {
	m_Function();
}