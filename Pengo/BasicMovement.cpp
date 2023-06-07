#include "BasicMovement.h"
#include "GameObject.h"
#include "InputDevice.h"
#include "InputManager.h"
#include "GameTime.h"
#include "MoveCommand.h"

using namespace pengo;

BasicMovement::BasicMovement(engine::GameObject* pOwner, float speed, engine::Keyboard* device)
	: BasicMovement(pOwner, speed)
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, m_MoveUp, device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, m_MoveDown, device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, m_MoveLeft, device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, m_MoveRight, device->GetID());
}

BasicMovement::BasicMovement(engine::GameObject* pOwner, float speed, engine::XBoxController* device)
	: BasicMovement(pOwner, speed)
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, m_MoveUp, device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, m_MoveDown, device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_LEFT, m_MoveLeft, device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_RIGHT, m_MoveRight, device->GetID());
}
BasicMovement::BasicMovement(engine::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MoveUp{ new MoveCommand(pOwner, glm::vec2{0,1}, speed)}
	, m_MoveDown{ new MoveCommand(pOwner, glm::vec2{0,-1}, speed)}
	, m_MoveLeft{ new MoveCommand(pOwner, glm::vec2{-1,0}, speed)}
	, m_MoveRight{ new MoveCommand(pOwner, glm::vec2{1,0}, speed)}
{
}