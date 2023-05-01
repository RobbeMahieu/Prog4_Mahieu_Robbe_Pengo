#pragma once
#include "Component.h"

class PointComponent : public Component
{
public:
	PointComponent(dae::GameObject* pOwner);
	virtual ~PointComponent() = default;

	PointComponent(const PointComponent& other) = delete;
	PointComponent(PointComponent&& other) = delete;
	PointComponent& operator=(const PointComponent& other) = delete;
	PointComponent& operator=(PointComponent&& other) = delete;

	virtual void Update([[maybe_unused]] float elapsedSec) {}
	virtual void FixedUpdate([[maybe_unused]] float elapsedSec) {}

	void AddScore(int amount);
	int GetScore();

protected:
	int m_CurrentScore;
};

