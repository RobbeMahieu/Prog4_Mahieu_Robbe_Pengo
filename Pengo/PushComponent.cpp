#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"

using namespace pengo;

PushComponent::PushComponent(engine::GameObject* pOwner, engine::Keyboard* device)
	: Component(pOwner)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new engine::Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, new engine::Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), engine::KeyState::OnRelease);
}

PushComponent::PushComponent(engine::GameObject* pOwner, engine::XBoxController* device)
	: Component(pOwner)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, new engine::Command(std::bind(&PushComponent::EnablePush, this, true)), device->GetID(), engine::KeyState::OnPress);
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, new engine::Command(std::bind(&PushComponent::EnablePush, this, false)), device->GetID(), engine::KeyState::OnRelease);
}

bool PushComponent::CanPush() const {

	return m_CanPush;

}

void PushComponent::EnablePush(bool enable){
	m_CanPush = enable;
}