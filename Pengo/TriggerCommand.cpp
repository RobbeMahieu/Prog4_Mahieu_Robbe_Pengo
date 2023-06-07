#include "TriggerCommand.h"

using namespace pengo;

TriggerCommand::TriggerCommand(bool* trigger, bool value)
	: Command()
	, m_Trigger{ trigger }
	, m_SetValue{ value }
{
}

void TriggerCommand::Execute() {
	*m_Trigger = m_SetValue;
}