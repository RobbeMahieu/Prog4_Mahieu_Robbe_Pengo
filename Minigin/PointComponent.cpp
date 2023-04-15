#include "PointComponent.h"
#include "EventManager.h"

PointComponent::PointComponent(dae::GameObject* pOwner)
	: Component(pOwner)
	, m_CurrentScore{ 0 }
{
}

void PointComponent::AddScore(int amount) {
	m_CurrentScore += amount;

	EventManager::GetInstance().Broadcast(EventType::ScoreIncrease, m_pOwner);
}

int PointComponent::GetScore() {
	return m_CurrentScore;
}