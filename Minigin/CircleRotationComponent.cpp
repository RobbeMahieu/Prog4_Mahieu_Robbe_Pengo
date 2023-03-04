#include "CircleRotationComponent.h"
#include "GameObject.h"

CircleRotationComponent::CircleRotationComponent(glm::vec3 orbitPoint, float speed, float distance)
	: Component()
	, m_OrbitPoint{ orbitPoint }
	, m_RotateSpeed{ speed }
	, m_Distance{ distance }
{}

void CircleRotationComponent::Update(float elapsedSec) {

	m_CurrentAngle += m_RotateSpeed * elapsedSec;

	glm::vec3 position = m_OrbitPoint;
	position.x += m_Distance * cosf(m_CurrentAngle);
	position.y += m_Distance * sinf(m_CurrentAngle);

	m_pGameObject->SetLocalPosition(position);

}