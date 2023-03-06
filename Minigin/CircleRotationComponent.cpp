#include "CircleRotationComponent.h"
#include "GameObject.h"

CircleRotationComponent::CircleRotationComponent(float speed, float distance)
	: Component()
	, m_RotateSpeed{ speed }
	, m_Distance{ distance }
{}

void CircleRotationComponent::Update(float elapsedSec) {

	m_CurrentAngle += m_RotateSpeed * elapsedSec;

	glm::vec3 pos{ m_Distance * cosf(m_CurrentAngle), m_Distance * sinf(m_CurrentAngle), 0.0f };

	m_pGameObject->SetLocalPosition(pos);

}