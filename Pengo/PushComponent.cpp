#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "TriggerCommand.h"

using namespace pengo;

PushComponent::PushComponent(engine::GameObject* pOwner, engine::Keyboard* device)
	: PushComponent(pOwner)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_ButtonPress, device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_ButtonRelease, device->GetID(), engine::KeyState::OnRelease);
}

PushComponent::PushComponent(engine::GameObject* pOwner, engine::XBoxController* device)
	: PushComponent(pOwner)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_ButtonPress, device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_ButtonRelease, device->GetID(), engine::KeyState::OnRelease);
}

PushComponent::PushComponent(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_ButtonPress{new TriggerCommand(&m_CanPush, true)}
	, m_ButtonRelease{new TriggerCommand(&m_CanPush, false)}
{
}

bool PushComponent::CanPush() const {

	return m_CanPush;

}

void PushComponent::EnablePush(bool enable){
	m_CanPush = enable;
}