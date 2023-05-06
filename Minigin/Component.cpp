#include "Component.h"
#include "GameObject.h"

Component::Component(dae::GameObject* pOwner)
	: m_pOwner{ pOwner}
	, m_IsMarkedForDestroy{ false }
{}

void Component::Destroy() {
	m_IsMarkedForDestroy = true;
}

bool Component::IsMarkedForDestroy() {
	return m_IsMarkedForDestroy;
}

dae::GameObject* Component::GetOwner() {
	return m_pOwner;
}