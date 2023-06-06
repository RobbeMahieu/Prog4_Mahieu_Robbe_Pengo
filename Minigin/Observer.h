#pragma once
#include <functional>

namespace engine {

	template<typename... Args>
	class Observer
	{
		public:
			explicit Observer() = default;
			virtual ~Observer() = default;

			Observer(const Observer& other) = delete;
			Observer(Observer&& other) = delete;
			Observer& operator=(const Observer& other) = delete;
			Observer& operator=(Observer&& other) = delete;

			virtual void OnNotify(Args... args) = 0;
	};
}

