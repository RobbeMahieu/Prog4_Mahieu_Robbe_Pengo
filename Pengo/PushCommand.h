#pragma once
#include <Command.h>
#include "GameObject.h"
#include <SubjectObserver.h>

namespace pengo {

	class SlidingComponent;
	class StunComponent;

	class PushCommand final : public engine::Command
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
		bool CanStun();

	private:
		engine::GameObject* m_pOwner;

		SlidingComponent* m_ClosestIce;
		StunComponent* m_ClosestWall;

		void Push();
		void Stun();
	};
}



