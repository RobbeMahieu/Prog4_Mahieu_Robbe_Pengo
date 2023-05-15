#include "GameServiceLocator.h"

std::unique_ptr<SoundSystem> GameServiceLocator::m_pSoundSystemInstance{ std::make_unique<NullSoundSystem>() };	

SoundSystem& GameServiceLocator::GetSoundSystem() {
	return *m_pSoundSystemInstance;
}

void GameServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss) { 
	m_pSoundSystemInstance = ss ? std::move(ss) : std::make_unique<NullSoundSystem>();
}