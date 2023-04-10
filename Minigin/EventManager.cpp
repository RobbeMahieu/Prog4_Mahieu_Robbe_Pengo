#include "EventManager.h"
#include "Observer.h"

void EventManager::AddListener(EventType event, Observer* pObserver) {

	// Create event if it doesn't exist
	if (m_pEvents.find(event) == m_pEvents.end()) {
		m_pEvents[event] = std::make_unique<Event>();
	}

	m_pEvents[event]->AddObserver(pObserver);
}

void EventManager::RemoveListener(EventType event, Observer* pObserver) {

	// Create event if it doesn't exist
	if (m_pEvents.find(event) == m_pEvents.end()) {
		m_pEvents[event] = std::make_unique<Event>();
	}

	m_pEvents[event]->RemoveObserver(pObserver);
}

void EventManager::RemoveListener(Observer* pObserver) {

	for (auto& event : m_pEvents) {
		if (event.second) {
			event.second->RemoveObserver(pObserver);
		}
	}
}

void EventManager::Broadcast(EventType event, dae::GameObject* invokingObject) {
	
	// Create event if it doesn't exist
	if (m_pEvents.find(event) == m_pEvents.end()) {
		m_pEvents[event] = std::make_unique<Event>();
	}

	m_pEvents[event]->Broadcast(invokingObject);
}