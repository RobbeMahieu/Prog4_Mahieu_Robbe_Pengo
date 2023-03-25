#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include <iterator>

void dae::GameObject::Destroy() {
	m_IsMarkedForDestroy = true;
}

bool dae::GameObject::IsMarkedForDestroy() {
	return m_IsMarkedForDestroy;
}

void dae::GameObject::Update(float elapsedSec){
	
	// Update
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { component->Update(elapsedSec); });
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) { child->Update(elapsedSec); });

	// Remove components marked for destroy
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { 
		if (component->IsMarkedForDestroy()) {
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
		}
	});

	// Remove children marked for destroy
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) { 
		if (child->IsMarkedForDestroy()) {
			m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
		}
	});
}

void dae::GameObject::FixedUpdate(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { component->FixedUpdate(elapsedSec); });
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) { child->FixedUpdate(elapsedSec); });
}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) { component->Render();	});
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) { child->Render(); });
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

void dae::GameObject::AttachTo(GameObject* pParent, bool keepWorldPosition) {

	// Update hierarchy
	std::unique_ptr<GameObject> child;

	if (m_pParent) {
		auto childIt = std::find_if(m_pParent->m_pChildren.begin(), m_pParent->m_pChildren.end(), [&](const auto& child) {
			return child.get() == this;
		});

		child = std::move(*childIt);
		m_pParent->m_pChildren.erase(childIt);
	}

	m_pParent = pParent;
	
	if (m_pParent) {

		// Make sure the unique pointer has a value (used first attach)
		if (!child.get()) {
			child.reset(this);
		}

		m_pParent->m_pChildren.push_back(std::move(child));
	}


	// Update position
	if (m_pParent == nullptr) {
		SetLocalPosition(GetWorldPosition());
		return;
	}

	if (keepWorldPosition) {
		SetLocalPosition(m_LocalPosition - m_pParent->GetWorldPosition());
	}

	m_PositionChanged = true;
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