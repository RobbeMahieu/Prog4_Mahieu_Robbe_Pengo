#include "BasicMovement.h"
#include "GameObject.h"
#include "InputDevice.h"
#include "InputManager.h"

#include "Keyboard.h"
#include "XBoxController.h"

BasicMovement::BasicMovement(dae::GameObject* pOwner, float speed, Keyboard* device)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,-1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ -1,0 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 1, 0})), device->GetID());
}

BasicMovement::BasicMovement(dae::GameObject* pOwner, float speed, XBoxController* device)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_UP, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,-1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_DOWN, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,1 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_LEFT, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ -1,0 })), device->GetID());
	dae::InputManager::GetInstance().BindAction(XBoxController::DPAD_RIGHT, new Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 1, 0 })), device->GetID());
}

void BasicMovement::Update(float elapsedSec) {

	glm::vec3 pos = m_pOwner->GetLocalPosition();
	pos.x += m_MovementSpeed * elapsedSec * m_MovementDirection.x;
	pos.y += m_MovementSpeed * elapsedSec * m_MovementDirection.y;
	m_pOwner->SetLocalPosition(pos);

	m_MovementDirection = { 0,0 };
}

void BasicMovement::Move(glm::vec2 direction) {
	m_MovementDirection+= direction;
}