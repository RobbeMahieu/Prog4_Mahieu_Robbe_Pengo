#include "LoggingSoundSystem.h"
#include <iostream>

using namespace engine;

LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& realSS)
	: m_RealSS{ std::move(realSS) }
{}

void LoggingSoundSystem::Play(const std::string& path, float volume) {
	m_RealSS->Play(path, volume);
	std::cout << "Playing: " << path << " at a volume of: " << volume << "\n";
}