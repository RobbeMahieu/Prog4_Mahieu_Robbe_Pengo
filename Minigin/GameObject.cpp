#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>
#include <iterator>
#include "RenderComponent.h"
#include "Component.h"

typedef std::pair<const std::string, std::unique_ptr<dae::Component>> NamedComponent;

void dae::GameObject::Update(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](NamedComponent& component) { component.second->Update(elapsedSec); });
}

void dae::GameObject::FixedUpdate(float elapsedSec){
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](NamedComponent& component) { component.second->FixedUpdate(elapsedSec); });
}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const NamedComponent& component) {

		const RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.second.get());
		if (renderComponent) {
			renderComponent->Render();
		}

	});
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() {
	return m_transform.GetPosition();
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


dae::Component* dae::GameObject::GetComponent(std::string name) const {
	
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