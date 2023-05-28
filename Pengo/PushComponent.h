#pragma once
#include <Component.h>
#include <glm/glm.hpp>

class Keyboard;
class XBoxController;

class PushComponent : public Component
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

		bool CanPush() const;
		void EnablePush(bool enable);

	private:
		bool m_CanPush{ false };

};

