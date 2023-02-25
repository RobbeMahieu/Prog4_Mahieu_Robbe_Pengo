#pragma once

namespace dae {

	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void FixedUpdate(float elapsedSec) = 0;
		void SetOwner(GameObject* gameObject);

	protected:
		GameObject* m_pGameObject{ nullptr };
	};

}

