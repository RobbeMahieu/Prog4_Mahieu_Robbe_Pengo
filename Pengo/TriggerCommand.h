#pragma once
#include <Command.h>
#include "GameObject.h"

// This is bad code due to the design of how pushing works
// Refactor ASAP

namespace pengo {

	class TriggerCommand : public engine::Command
	{
	public:
		explicit TriggerCommand(bool* trigger, bool value);
		virtual ~TriggerCommand() = default;

		TriggerCommand(const TriggerCommand& other) = delete;
		TriggerCommand(TriggerCommand&& other) = delete;
		TriggerCommand& operator=(const TriggerCommand& other) = delete;
		TriggerCommand& operator=(TriggerCommand&& other) = delete;

		virtual void Execute() override;

	private:
		bool* m_Trigger;
		bool m_SetValue;
	};
}



