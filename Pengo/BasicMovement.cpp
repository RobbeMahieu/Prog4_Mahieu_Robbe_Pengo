#include "BasicMovement.h"
#include "GameObject.h"
#include "InputDevice.h"
#include "InputManager.h"

using namespace pengo;

BasicMovement::BasicMovement(engine::GameObject* pOwner, float speed, engine::Keyboard* device)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_W, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,-1 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_S, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,1 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_A, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ -1,0 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(SDL_SCANCODE_D, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 1, 0})), device->GetID());
}

BasicMovement::BasicMovement(engine::GameObject* pOwner, float speed, engine::XBoxController* device)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_UP, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,-1 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_DOWN, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 0,1 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_LEFT, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ -1,0 })), device->GetID());
	engine::InputManager::GetInstance().BindAction(engine::XBoxController::DPAD_RIGHT, new engine::Command(std::bind(&BasicMovement::Move, this, glm::vec2{ 1, 0 })), device->GetID());
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