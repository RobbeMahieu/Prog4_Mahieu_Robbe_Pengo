#include "Event.h"
#include "Observer.h"
#include "GameObject.h"

void Event::AddObserver(Observer* pObserver) {
	m_pObservers.push_back(pObserver);
}

void Event::RemoveObserver(Observer* pObserver) {
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
}

void Event::Broadcast(dae::GameObject* invokingObject) {
	for (Observer* pObserver : m_pObservers) {
		pObserver->Execute(invokingObject);
	}
}