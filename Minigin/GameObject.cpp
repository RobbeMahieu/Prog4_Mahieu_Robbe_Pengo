#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include <iterator>

using namespace engine;

void GameObject::Destroy() {
	m_IsMarkedForDestroy = true;

	// Destroy children
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) {
		child->Destroy();
	});

	// Destroy components
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) {
		component->Destroy();
	});
}

bool GameObject::IsMarkedForDestroy() {
	return m_IsMarkedForDestroy;
}

void GameObject::Update(){
	
	// Update 
	// Needs to be an indexed loop cause components/children can be added and will mess up the iterators
	for (int i{ 0 }; i < m_pComponents.size(); ++i) {
		m_pComponents[i]->Update();
	}

	for (int i{ 0 }; i < m_pChildren.size(); ++i) {
		m_pChildren[i]->Update();
	}

	// Remove components children marked for destroy
	m_pChildren.erase(std::remove_if(m_pChildren.begin(), m_pChildren.end(), [](auto& child) {return child->IsMarkedForDestroy(); }), m_pChildren.end());
	m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](auto& component) {return component->IsMarkedForDestroy(); }), m_pComponents.end());
}

void GameObject::FixedUpdate(){
	// Needs to be an indexed loop cause components/children can be added and will mess up the iterators
	for (int i{ 0 }; i < m_pComponents.size(); ++i) {
		m_pComponents[i]->FixedUpdate();
	}

	for (int i{ 0 }; i < m_pChildren.size(); ++i) {
		m_pChildren[i]->FixedUpdate();
	}
}

void GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) { component->Render();	});
	std::for_each(m_pChildren.begin(), m_pChildren.end(), [=](auto& child) { child->Render(); });
}

void GameObject::SetLocalPosition(float x, float y)
{
	m_LocalPosition = glm::vec3{ round(x), round(y), 0.0f };
	m_PositionChanged = true;
}

void GameObject::SetLocalPosition(glm::vec3 position)
{
	SetLocalPosition(position.x, position.y);
}

void GameObject::SetWorldPosition(float x, float y)
{
	m_LocalPosition = glm::vec3{ round(x), round(y), 0.0f };
	if (m_pParent) {
		m_LocalPosition -=	m_pParent->GetWorldPosition();
	}
	m_PositionChanged = true;
}

void GameObject::SetWorldPosition(glm::vec3 position)
{
	SetWorldPosition(position.x, position.y);
}

glm::vec3 GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

glm::vec3 GameObject::GetWorldPosition() {

	if (HasPositionChanged()) {
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void GameObject::AttachTo(GameObject* pParent, bool keepWorldPosition) {

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

void GameObject::UpdateWorldPosition() {
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

bool GameObject::HasPositionChanged() {

	if (m_pParent) {
		m_PositionChanged = m_PositionChanged || m_pParent->HasPositionChanged();
	}

	return m_PositionChanged;
}

std::vector<GameObject*> GameObject::GetChildren() const{
	std::vector<GameObject*> children{};

	std::transform(m_pChildren.begin(), m_pChildren.end(), std::inserter(children, children.begin()), [](auto& element) { return element.get(); });

	return children;
}

GameObject* GameObject::GetParent() const {
	return m_pParent;
}