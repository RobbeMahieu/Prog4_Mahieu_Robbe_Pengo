#pragma once
#include <string>

namespace engine {

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string&, float) = 0;
		virtual void PlayMusic(const std::string&, float) = 0;
		virtual void SetMute(bool mute) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Play(const std::string&, float) override {}
		void PlayMusic(const std::string&, float) override {}
		void SetMute(bool) override {}
	};

}
