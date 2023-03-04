#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class CircleRotationComponent : public dae::Component
{

public:
	CircleRotationComponent( glm::vec3 orbitPoint, float speed, float distance );
	virtual ~CircleRotationComponent() = default;

	CircleRotationComponent(const CircleRotationComponent& other) = delete;
	CircleRotationComponent(CircleRotationComponent&& other) = delete;
	CircleRotationComponent& operator=(const CircleRotationComponent& other) = delete;
	CircleRotationComponent& operator=(CircleRotationComponent&& other) = delete;

	virtual void Update(float elapsedSec);
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

protected:
	float m_Distance{ 30.0f };
	float m_CurrentAngle{ 0.0f };
	float m_RotateSpeed{ 5.0f };
	glm::vec3 m_OrbitPoint;
};

