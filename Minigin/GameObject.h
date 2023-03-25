#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include "Component.h"

namespace dae
{
	class GameObject final
	{
		public:

			GameObject() = default;
			~GameObject() = default;

			GameObject(const GameObject& other) = delete;
			GameObject(GameObject&& other) = delete;
			GameObject& operator=(const GameObject& other) = delete;
			GameObject& operator=(GameObject&& other) = delete;

			void Update(float elapsedSec);
			void FixedUpdate(float elapsedSec);
			void Render() const;

			void SetLocalPosition(float x, float y);
			void SetLocalPosition(glm::vec3 position);
			glm::vec3 GetLocalPosition();
			glm::vec3 GetWorldPosition();
			bool HasPositionChanged();

			template<typename ComponentType, typename... Args>
			ComponentType* AddComponent(Args&&... arguments) {
				std::unique_ptr<ComponentType> component{ std::make_unique<ComponentType>(this, std::forward<Args>(arguments)...) };
				m_pComponents.push_back(std::move(component));
				return GetComponent<ComponentType>();
			}

			template<typename ComponentType>
			ComponentType* GetComponent() const {
				auto foundComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {				
					return typeid(*(component.get())) == typeid(ComponentType);
				});

				if (foundComponent != m_pComponents.end()) {
					return static_cast<ComponentType*>((*foundComponent).get());
				}
				return nullptr;
			}

			template<typename ComponentType>
			std::vector<ComponentType*> GetComponents() const {

				std::vector<ComponentType*> pComponents{};

				std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](const auto& component) {
					if (typeid(*(component.get())) == typeid(ComponentType)) {
						pComponents.push_back(static_cast<ComponentType*>(component.get()));
					}
				});

				return pComponents;
			}

			template<typename ComponentType>
			bool RemoveComponent() const {
				auto foundComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
					return typeid(*(component.get())) == typeid(ComponentType);
				});

				if (foundComponent != m_pComponents.end()) {
					(*foundComponent)->Destroy();
					return true;
				}
				return false;
			}

			template<typename ComponentType>
			void RemoveComponents() const {

				std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](auto& component) {
					if (typeid(*(component.get())) == typeid(ComponentType)) {
						component->Destroy();
					}
				});
			}

			void AttachTo(GameObject* pParent, bool keepWorldPosition);
			bool IsMarkedForDestroy();			
			void Destroy();

		private:
			void UpdateWorldPosition();

			glm::vec3 m_LocalPosition{};
			glm::vec3 m_WorldPosition{};
			bool m_PositionChanged{ false };
			bool m_IsMarkedForDestroy{ false };

			std::vector<std::unique_ptr<Component>> m_pComponents;

			GameObject* m_pParent{ nullptr };
			std::vector<std::unique_ptr<GameObject>> m_pChildren;
	};
}
