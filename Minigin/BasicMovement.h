#pragma once
#include "Component.h"
#include "glm/glm.hpp"

class BasicMovement : public Component
{
public:
	BasicMovement(dae::GameObject* pOwner, float speed);
	virtual ~BasicMovement() = default;

	BasicMovement(const BasicMovement& other) = delete;
	BasicMovement(BasicMovement&& other) = delete;
	BasicMovement& operator=(const BasicMovement& other) = delete;
	BasicMovement& operator=(BasicMovement&& other) = delete;

	virtual void Update(float elapsedSec);
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

protected:
	float m_MovementSpeed;
	glm::vec2 m_MovementDirection{ 0,0 };
};

