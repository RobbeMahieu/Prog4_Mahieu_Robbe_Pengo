#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include <iterator>
#include "Component.h"

typedef std::pair<const std::string, std::unique_ptr<Component>> NamedComponent;

void dae::GameObject::Update(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](NamedComponent& component) { component.second->Update(elapsedSec); });
}

void dae::GameObject::FixedUpdate(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](NamedComponent& component) { component.second->FixedUpdate(elapsedSec); });
}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const NamedComponent& component) { component.second->Render();	});
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

bool dae::GameObject::AddComponent(std::string name, std::unique_ptr<Component> component) {
	// Component with that name already exists
	if (m_pComponents.count(name)) {
		return false;
	}
	
	component->SetOwner(this);
	m_pComponents[name] = std::move(component);
	return true;
}


Component* dae::GameObject::GetComponent(std::string name) const {
	
	if (m_pComponents.count(name)) {
		return m_pComponents.find(name)->second.get();
	}

	return nullptr;
}

bool dae::GameObject::RemoveComponent(std::string name) {

	if (m_pComponents.count(name)) {
		m_pComponents.erase(name);
		return true;
	}

	return false;
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