#pragma once
#include <Command.h>
#include "GameObject.h"

namespace pengo {

	class SlidingComponent;

	class PushCommand : public engine::Command
	{
	public:
		explicit PushCommand(engine::GameObject* pOwner);
		virtual ~PushCommand() = default;

		PushCommand(const PushCommand& other) = delete;
		PushCommand(PushCommand&& other) = delete;
		PushCommand& operator=(const PushCommand& other) = delete;
		PushCommand& operator=(PushCommand&& other) = delete;

		virtual void Execute() override;
		bool CanPush();

	private:
		engine::GameObject* m_pOwner;

		SlidingComponent* m_ClosestIce;
	};
}



