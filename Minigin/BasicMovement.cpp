#include "BasicMovement.h"
#include "GameObject.h"

BasicMovement::BasicMovement(dae::GameObject* pOwner, float speed)
	: Component(pOwner)
	, m_MovementSpeed{ speed }
{}

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