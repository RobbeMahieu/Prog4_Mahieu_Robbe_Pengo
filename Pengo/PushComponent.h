#pragma once
#include <Component.h>
#include <glm/glm.hpp>
#include "Observer.h"
#include "CollisionComponent.h"

class Keyboard;
class XBoxController;

class PushComponent : public Component, public Observer<CollisionComponent*>
{
	public:
		PushComponent(dae::GameObject* pOwner, Keyboard* device);
		PushComponent(dae::GameObject* pOwner, XBoxController* device);
		virtual ~PushComponent() = default;

		PushComponent(const PushComponent& other) = delete;
		PushComponent(PushComponent&& other) = delete;
		PushComponent& operator=(const PushComponent& other) = delete;
		PushComponent& operator=(PushComponent&& other) = delete;

		virtual void Update(float /*elapsedSec*/) {};
		virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

		void OnNotify(CollisionComponent* other);
		void EnablePush(bool enable);
		void SetPushDirection(glm::vec2 direction);

	private:
		glm::vec2 m_PushDirection{ 0,0 };
		bool m_CanPush{ false };

};

