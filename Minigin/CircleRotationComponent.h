#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class CircleRotationComponent : public Component
{

public:
	CircleRotationComponent(dae::GameObject* pOwner, float speed, float distance );
	virtual ~CircleRotationComponent() = default;

	CircleRotationComponent(const CircleRotationComponent& other) = delete;
	CircleRotationComponent(CircleRotationComponent&& other) = delete;
	CircleRotationComponent& operator=(const CircleRotationComponent& other) = delete;
	CircleRotationComponent& operator=(CircleRotationComponent&& other) = delete;

	virtual void Update(float elapsedSec);
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

protected:
	float m_Distance;
	float m_CurrentAngle;
	float m_RotateSpeed;
};

