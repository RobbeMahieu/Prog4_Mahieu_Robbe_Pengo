#include "BasicMovement.h"
#include "GameObject.h"
#include "InputDevice.h"
#include "InputManager.h"

#include "Keyboard.h"
#include "XBoxController.h"

BasicMovement::BasicMovement(dae::GameObject* pOwner, float speed, InputDevice* device)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{

	int upKey{ typeid(*device) == typeid(Keyboard) ? SDL_SCANCODE_W : XBoxController::ControllerButton::DPAD_UP };
	int downKey{ typeid(*device) == typeid(Keyboard) ? SDL_SCANCODE_S : XBoxController::ControllerButton::DPAD_DOWN };
	int leftKey{ typeid(*device) == typeid(Keyboard) ? SDL_SCANCODE_A : XBoxController::ControllerButton::DPAD_LEFT };
	int rightKey{ typeid(*device) == typeid(Keyboard) ? SDL_SCANCODE_D : XBoxController::ControllerButton::DPAD_RIGHT };

	dae::InputManager::GetInstance().BindAction(upKey, new Command(std::bind(&BasicMovement::MoveUp, this)), device->GetID());
	dae::InputManager::GetInstance().BindAction(downKey, new Command(std::bind(&BasicMovement::MoveDown, this)), device->GetID());
	dae::InputManager::GetInstance().BindAction(leftKey, new Command(std::bind(&BasicMovement::MoveLeft, this)), device->GetID());
	dae::InputManager::GetInstance().BindAction(rightKey, new Command(std::bind(&BasicMovement::MoveRight, this)), device->GetID());
}

void BasicMovement::Update(float elapsedSec) {

	glm::vec3 pos = m_pOwner->GetLocalPosition();
	pos.x += m_MovementSpeed * elapsedSec * m_MovementDirection.x;
	pos.y += m_MovementSpeed * elapsedSec * m_MovementDirection.y;
	m_pOwner->SetLocalPosition(pos);

	m_MovementDirection = { 0,0 };
}

void BasicMovement::MoveUp() {
	m_MovementDirection.y -= 1.0f;
}

void BasicMovement::MoveDown(){
	m_MovementDirection.y += 1.0f;
}

void BasicMovement::MoveLeft(){
	m_MovementDirection.x -= 1.0f;
}

void BasicMovement::MoveRight(){
	m_MovementDirection.x += 1.0f;
}