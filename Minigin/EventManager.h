#pragma once
#include "Singleton.h"
#include "EventList.h"
#include "Event.h"
#include <unordered_map>
#include <memory>

namespace dae {
	class GameObject;
}

class Observer;

class EventManager final : public dae::Singleton<EventManager>
{
	public:
		void AddListener(EventType event, Observer* pObserver);
		void RemoveListener(EventType event, Observer* pObserver);
		void RemoveListener(Observer* pObserver);
		void Broadcast(EventType event, dae::GameObject* invokingObject);

	private:
		friend class Singleton<EventManager>;
		EventManager() = default;

		std::unordered_map<EventType, std::unique_ptr<Event>> m_pEvents;
};

