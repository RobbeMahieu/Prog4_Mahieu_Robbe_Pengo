#include "Observer.h"
#include "EventManager.h"
#include "GameObject.h"

Observer::Observer(const std::function<void(dae::GameObject*)>& function) 
	: m_Function{ function }
{
}

Observer::~Observer() {
	// For some reason, the events get destroyed before the observer, so doing this crashed the game...
	//EventManager::GetInstance().RemoveListener(this);
}

void Observer::Execute(dae::GameObject* invokingObject) {
	m_Function(invokingObject);
}