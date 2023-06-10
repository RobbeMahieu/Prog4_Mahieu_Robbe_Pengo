#include "GameTime.h"

using namespace engine;

void GameTime::Init() {
	m_StartTime = std::chrono::high_resolution_clock::now();
	m_LastFrameTime = m_StartTime;
	m_FixedUpdateStep = 0.005f;
}

void GameTime::Update() {
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastFrameTime).count();
	m_LastFrameTime = currentTime;
}

float GameTime::GetElapsedSec() const {
	return m_DeltaTime;
}

float GameTime::GetTotalSec() const{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<float>(currentTime - m_StartTime).count();
}

std::chrono::steady_clock::time_point GameTime::GetFrameStartTime() const {
	return m_LastFrameTime;
}

float GameTime::GetFixedUpdateStep() const {
	return m_FixedUpdateStep;
}