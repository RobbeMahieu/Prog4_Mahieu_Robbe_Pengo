#include "PointComponent.h"

using namespace pengo;

PointComponent::PointComponent(engine::GameObject* pOwner)
	: Component(pOwner)
	, m_Score{0}
{
}

void PointComponent::AddScore(int amount) {
	m_Score += amount;
	ScoreChanged.Broadcast(m_Score);
}

void PointComponent::SetScore(int newScore) {
	m_Score = newScore;
	ScoreChanged.Broadcast(m_Score);
}

int PointComponent::GetScore() {
	return m_Score;
}