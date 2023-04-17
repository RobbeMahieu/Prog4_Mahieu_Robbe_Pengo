#pragma once
#include <functional>
#include "EventList.h"

namespace dae {
	class GameObject;
}

class Observer
{
	public:
		explicit Observer() = default;
		virtual ~Observer();

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void OnNotify(EventType event, dae::GameObject* invokingObject) = 0;

};

