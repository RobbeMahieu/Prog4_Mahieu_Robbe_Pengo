#include "PlayerMovement.h"
#include "GameObject.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "GameTime.h"
#include "MoveCommand.h"
#include "PushCommand.h"
#include "glm/glm.hpp"

using namespace pengo;

PlayerMovement::PlayerMovement(engine::GameObject* pOwner, float speed, engine::Keyboard* device)
	: PlayerMovement(pOwner, speed)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, m_MoveUp.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, m_MoveDown.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, m_MoveLeft.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, m_MoveRight.get(), device->GetID());
}

PlayerMovement::PlayerMovement(engine::GameObject* pOwner, float speed, engine::XBoxController* device)
	: PlayerMovement(pOwner, speed)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, m_MoveUp.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, m_MoveDown.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_LEFT, m_MoveLeft.get(), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_RIGHT, m_MoveRight.get(), device->GetID());
}
PlayerMovement::PlayerMovement(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MoveUp{ std::make_unique<MoveCommand>(pOwner, glm::vec2{0,-1}, speed)}
	, m_MoveDown{ std::make_unique<MoveCommand>(pOwner, glm::vec2{0,1}, speed)}
	, m_MoveLeft{ std::make_unique<MoveCommand>(pOwner, glm::vec2{-1,0}, speed)}
	, m_MoveRight{ std::make_unique<MoveCommand>(pOwner, glm::vec2{1,0}, speed)}
{
}

