#pragma once
#include "SoundSystem.h"
#include <memory>

namespace engine {

	class LoggingSoundSystem : public SoundSystem
	{
		public:
			LoggingSoundSystem(std::unique_ptr<SoundSystem>&& realSS);
			virtual ~LoggingSoundSystem() = default;

			LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
			LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
			LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
			LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

			void Play(const std::string& path, float volume) override;
			void PlayMusic(const std::string& path, float volume) override;
			void SetMute(bool mute) override;

		private:
			std::unique_ptr<SoundSystem> m_RealSS;
	};
}

