#include "PushComponent.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "PushCommand.h"
#include "SlidingComponent.h"

using namespace pengo;

PushComponent::PushComponent(engine::GameObject* pOwner, engine::Keyboard* device)
	: PushComponent(pOwner)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_SPACE, m_Push, device->GetID(), engine::KeyState::OnPress);
}

PushComponent::PushComponent(engine::GameObject* pOwner, engine::XBoxController* device)
	: PushComponent(pOwner)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::BUTTON_A, m_Push, device->GetID(), engine::KeyState::OnPress);
}

PushComponent::PushComponent(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_Push{ new PushCommand(m_pOwner) }
{
}
