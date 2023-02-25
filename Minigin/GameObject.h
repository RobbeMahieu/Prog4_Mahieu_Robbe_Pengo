#pragma once
#include <memory>
#include "Transform.h"
#include <unordered_map>

namespace dae
{
	class Component;

	class GameObject final
	{
		public:

			void Update(float elapsedSec);
			void FixedUpdate(float elapsedSec);
			void Render() const;

			void SetPosition(float x, float y);
			glm::vec3 GetPosition();

			bool AddComponent(std::string name, std::unique_ptr<Component> component);
			Component* GetComponent(std::string name) const;
			bool RemoveComponent(std::string name);

		private:
			Transform m_transform{};
			std::unordered_map<std::string, std::unique_ptr<Component>> m_pComponents;
	};
}
