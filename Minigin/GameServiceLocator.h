#pragma once
#include <memory>
#include "SoundSystem.h"

class SoundSystem;

class GameServiceLocator final
{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);

	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
};

