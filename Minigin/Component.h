#pragma once

namespace engine {

	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject* pOwner);
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void FixedUpdate(float elapsedSec) = 0;
		virtual void Render() const {};

		void Destroy();
		bool IsMarkedForDestroy();
		GameObject* GetOwner();

	protected:
		GameObject* m_pOwner;
		bool m_IsMarkedForDestroy;
	};
}



