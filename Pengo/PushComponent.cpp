#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include <unordered_set>
#include "SlidingComponent.h"

#include "Keyboard.h"
#include "XBoxController.h"

PushComponent::PushComponent(dae::GameObject* pOwner, Keyboard* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&PushComponent::Push, this)), device->GetID());
}

PushComponent::PushComponent(dae::GameObject* pOwner, XBoxController* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PushComponent::Push, this)), device->GetID());
}

void PushComponent::Push() {
	CollisionComponent* collider = m_pOwner->GetComponent<CollisionComponent>();
	const auto otherColliders = collider->GetColliding();

	SlidingComponent* closestIce = nullptr;
	float closestDistance{ FLT_MAX };

	// Find closest ice
	for (const auto& other : otherColliders) {
		SlidingComponent* slidingComponent{ other->GetOwner()->GetComponent<SlidingComponent>() };

		if (slidingComponent) {

			// First ice
			if (!closestIce) {
				closestIce = slidingComponent;
				continue;
			}

			float distance{ glm::distance(m_pOwner->GetWorldPosition(), slidingComponent->GetOwner()->GetWorldPosition()) };
			if (distance < closestDistance) {
				closestIce = slidingComponent;
				closestDistance = distance;
			}
		}
	}

	if (closestIce) {
		float xDistance{ closestIce->GetOwner()->GetWorldPosition().x - m_pOwner->GetWorldPosition().x };
		float yDistance{ closestIce->GetOwner()->GetWorldPosition().y - m_pOwner->GetWorldPosition().y };

		glm::vec2 direction{ (abs(xDistance) > abs(yDistance) ? glm::vec2{xDistance / abs(xDistance), 0 } : glm::vec2{0, yDistance / abs(yDistance) }) };

		closestIce->StartSliding(direction);

	}

}