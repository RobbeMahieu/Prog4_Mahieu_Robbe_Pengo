#pragma once
#include "SoundSystem.h"
#include <memory>

namespace engine {

	class SDL_SoundSystem final : public SoundSystem
	{
		public:

			SDL_SoundSystem();
			virtual ~SDL_SoundSystem();

			SDL_SoundSystem(const SDL_SoundSystem& other) = delete;
			SDL_SoundSystem(SDL_SoundSystem&& other) = delete;
			SDL_SoundSystem& operator=(const SDL_SoundSystem& other) = delete;
			SDL_SoundSystem& operator=(SDL_SoundSystem&& other) = delete;

			void Play(const std::string& path, float volume);

		private:

			// Pimple
			class SDL_SoundSystemImpl;
			std::unique_ptr<SDL_SoundSystemImpl> pImpl;
	};

}
