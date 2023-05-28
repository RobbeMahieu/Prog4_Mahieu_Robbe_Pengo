#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"

#include "Keyboard.h"
#include "XBoxController.h"

PushComponent::PushComponent(dae::GameObject* pOwner, Keyboard* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), KeyState::OnRelease);
}

PushComponent::PushComponent(dae::GameObject* pOwner, XBoxController* device)
	: Component(pOwner)
{
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), KeyState::OnPress);
	dae::InputManager::GetInstance().BindAction(XBoxController::BUTTON_A, new Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), KeyState::OnRelease);
}

bool PushComponent::CanPush() const {

	return m_CanPush;

}

void PushComponent::EnablePush(bool enable){
	m_CanPush = enable;
}