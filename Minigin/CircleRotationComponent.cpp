#include "CircleRotationComponent.h"
#include "GameObject.h"

CircleRotationComponent::CircleRotationComponent(dae::GameObject* pOwner, float speed, float distance)
	: Component(pOwner)
	, m_RotateSpeed{ speed }
	, m_Distance{ distance }
	, m_CurrentAngle{ 0.0f }
{}

void CircleRotationComponent::Update(float elapsedSec) {

	m_CurrentAngle += m_RotateSpeed * elapsedSec;

	glm::vec3 pos{ m_Distance * cosf(m_CurrentAngle), m_Distance * sinf(m_CurrentAngle), 0.0f };

	m_pOwner->SetLocalPosition(pos);

}