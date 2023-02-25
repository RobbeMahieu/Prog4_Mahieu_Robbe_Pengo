#include "Component.h"
#include "GameObject.h"

void dae::Component::SetOwner(dae::GameObject* gameObject) {
	m_pGameObject = gameObject;
}