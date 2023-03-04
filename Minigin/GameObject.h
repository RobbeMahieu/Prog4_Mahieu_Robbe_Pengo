#pragma once
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>

namespace dae
{
	class Component;

	class GameObject final
	{
		public:

			void Update(float elapsedSec);
			void FixedUpdate(float elapsedSec);
			void Render() const;

			void SetLocalPosition(float x, float y);
			void SetLocalPosition(glm::vec3 position);
			glm::vec3 GetWorldPosition();
			bool HasPositionChanged();

			bool AddComponent(std::string name, std::unique_ptr<Component> component);
			Component* GetComponent(std::string name) const;
			bool RemoveComponent(std::string name);

			void SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition);

		private:
			void UpdateWorldPosition();

			glm::vec3 m_LocalPosition{};
			glm::vec3 m_WorldPosition{};
			bool m_PositionChanged;

			std::unordered_map<std::string, std::unique_ptr<Component>> m_pComponents;

			std::shared_ptr<GameObject> m_pParent;
	};
}
