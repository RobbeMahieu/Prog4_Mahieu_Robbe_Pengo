#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include <unordered_set>
#include "SlidingComponent.h"
#include <GameServiceLocator.h>

#include "Keyboard.h"
#include "XBoxController.h"

PushComponent::PushComponent(dae::GameObject* pOwner, Keyboard* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), KeyState::OnRelease);

	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 0,-1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 0,1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ -1,0 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 1, 0 })), device->GetID());

	m_pOwner->GetComponent<CollisionComponent>()->Collides.AddObserver(this);
}

PushComponent::PushComponent(dae::GameObject* pOwner, XBoxController* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), KeyState::OnRelease);

	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_UP, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 0,-1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_DOWN, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 0,1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_LEFT, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ -1,0 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_RIGHT, new Command(std::bind(&PushComponent::SetPushDirection, this, glm::vec2{ 1, 0 })), device->GetID());

	m_pOwner->GetComponent<CollisionComponent>()->Collides.AddObserver(this);
}

void PushComponent::OnNotify(CollisionComponent* iceBlock) {

	SlidingComponent* slidingComponent{ iceBlock->GetOwner()->GetComponent<SlidingComponent>() };

	if (slidingComponent && m_CanPush) {
		m_CanPush = false;
		slidingComponent->StartSliding(m_PushDirection);

		// Play Sound
		auto& ss = GameServiceLocator::GetSoundSystem();
		ss.Play("../Data/Sounds/Push.wav", 1.0f);
	}

}

void PushComponent::EnablePush(bool enable){
	m_CanPush = enable;
}

void PushComponent::SetPushDirection(glm::vec2 direction) {
	m_PushDirection = direction;
}