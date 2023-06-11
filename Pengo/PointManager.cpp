#include "PointManager.h"
#include "PushComponent.h"
#include "GameManager.h"
#include <sstream>
#include <iomanip>

using namespace pengo;

void PointManager::AddScore(int amount) {
	m_Score += amount;
	ScoreChanged.Broadcast(m_Score);
}

int PointManager::GetScore() {
	return m_Score;
}

std::string PointManager::GetScoreText() {
	std::stringstream ss;
	ss << std::setw(8) << std::setfill('0') << m_Score;
	return ss.str();
}

void PointManager::ResetScore() {
	m_Score = 0;
	ScoreChanged.Broadcast(m_Score);
}
