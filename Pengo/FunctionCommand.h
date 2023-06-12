#pragma once
#include <Command.h>
#include <GameObject.h>
#include <functional>

namespace pengo {
	
	class FunctionCommand final : public engine::Command
	{
		public:
			explicit FunctionCommand(const std::function<void()>& function);
			virtual ~FunctionCommand() = default;

			FunctionCommand(const FunctionCommand& other) = delete;
			FunctionCommand(FunctionCommand&& other) = delete;
			FunctionCommand& operator=(const FunctionCommand& other) = delete;
			FunctionCommand& operator=(FunctionCommand&& other) = delete;

			virtual void Execute() override;

		private:
			const std::function<void()> m_Function;
	};
}
