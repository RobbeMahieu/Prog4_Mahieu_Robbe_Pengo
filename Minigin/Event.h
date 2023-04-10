#pragma once
#include <vector>

namespace dae {
	class GameObject;
}

class Observer;

class Event
{
	public:
		Event() = default;
		~Event() = default;

		Event(const Event& other) = delete;
		Event(Event&& other) = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void Broadcast(dae::GameObject* invokingObject);

	private:
		std::vector<Observer*> m_pObservers;

};

