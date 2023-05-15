#pragma once
#include <string>

class SoundSystem
{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string&, float ) = 0;
};

class NullSoundSystem final : public SoundSystem
{
	void Play(const std::string&, float) override {}
};

