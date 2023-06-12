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

void LoggingSoundSystem::PlayMusic(const std::string& path, float volume) {
	m_RealSS->PlayMusic(path, volume);
	std::cout << "Playing song: " << path << " at a volume of: " << volume << "\n";
}

void LoggingSoundSystem::SetMute(bool mute) {
	m_RealSS->SetMute(mute);
	std::cout << "Setting mute: " << mute;
}