#include "Component.h"
#include "GameObject.h"

using namespace engine;

Component::Component(GameObject* pOwner)
	: m_pOwner{ pOwner}
	, m_IsMarkedForDestroy{ false }
{}

void Component::Destroy() {
	m_IsMarkedForDestroy = true;
}

bool Component::IsMarkedForDestroy() {
	return m_IsMarkedForDestroy;
}

GameObject* Component::GetOwner() {
	return m_pOwner;
}