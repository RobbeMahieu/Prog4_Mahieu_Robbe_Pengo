#pragma once
#include "Component.h"
#include "Subject.h"

class PointComponent final : public Component
{
public:
	PointComponent(dae::GameObject* pOwner);
	virtual ~PointComponent() = default;

	PointComponent(const PointComponent& other) = delete;
	PointComponent(PointComponent&& other) = delete;
	PointComponent& operator=(const PointComponent& other) = delete;
	PointComponent& operator=(PointComponent&& other) = delete;

	virtual void Update(float /*elapsedSec*/) {}
	virtual void FixedUpdate(float /*elapsedSec*/) {}

	void AddScore(int amount);
	int GetScore();

private:
	int m_Score;

	void SetScore(int newScore);

public:
	Subject<int> ScoreChanged;
};

