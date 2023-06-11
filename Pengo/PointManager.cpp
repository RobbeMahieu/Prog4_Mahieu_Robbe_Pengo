#include "PointManager.h"
#include "PushComponent.h"
#include "GameManager.h"

using namespace pengo;

void PointManager::AddScore(int amount) {
	m_Score += amount;
	ScoreChanged.Broadcast(m_Score);
}

int PointManager::GetScore() {
	return m_Score;
}
