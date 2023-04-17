#include "Observer.h"
#include "EventManager.h"
#include "GameObject.h"

Observer::~Observer() {
	// For some reason, the events get destroyed before the observer, so doing this crashed the game...
	//EventManager::GetInstance().RemoveListener(this);
}
