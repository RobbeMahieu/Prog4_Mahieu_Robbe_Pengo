#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include <iterator>
#include "Component.h"

void dae::GameObject::Update(float elapsedSec){
	// Update
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { component->Update(elapsedSec); });

	// Remove objects marked for delete
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { 
		if (component->IsMarkedForDestroy()) {
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
		}
	});
}

void dae::GameObject::FixedUpdate(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { component->FixedUpdate(elapsedSec); });
}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) { component->Render();	});
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_LocalPosition = glm::vec3{ x,y, 0.0f };
	m_PositionChanged = true;
}

void dae::GameObject::SetLocalPosition(glm::vec3 position)
{
	SetLocalPosition(position.x, position.y);
}

glm::vec3 dae::GameObject::GetWorldPosition() {

	if (HasPositionChanged()) {
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition) {

	// Update hierarchy
	if (m_pParent) {
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;
	if (m_pParent) {
		m_pParent->AddChild(this);
	}

	// Update positions
	if (pParent == nullptr) {
		SetLocalPosition(GetWorldPosition());
		return;
	}

	if (keepWorldPosition) {
		SetLocalPosition(m_LocalPosition - m_pParent->GetWorldPosition());
	}

	m_PositionChanged = true;
}

void dae::GameObject::AddChild(GameObject* pChild) {
	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild) {
	m_pChildren.erase(remove(m_pChildren.begin(), m_pChildren.end(), pChild), m_pChildren.end());
}

void dae::GameObject::UpdateWorldPosition() {
	if (HasPositionChanged()) {
		if (m_pParent) {
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
		}
		else {
			m_WorldPosition = m_LocalPosition;
		}
	}
	m_PositionChanged = false;
}

bool dae::GameObject::HasPositionChanged() {

	if (m_pParent) {
		m_PositionChanged = m_PositionChanged || m_pParent->HasPositionChanged();
	}

	return m_PositionChanged;
}