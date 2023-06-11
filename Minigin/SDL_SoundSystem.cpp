#include "SDL_SoundSystem.h"
#include <iostream>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <SDL_mixer.h>
#include <unordered_map>

using namespace engine;

class SDL_SoundSystem::SDL_SoundSystemImpl {
	public:
		SDL_SoundSystemImpl();
		~SDL_SoundSystemImpl();

		SDL_SoundSystemImpl(const SDL_SoundSystemImpl& other) = delete;
		SDL_SoundSystemImpl(SDL_SoundSystemImpl&& other) = delete;
		SDL_SoundSystemImpl& operator=(const SDL_SoundSystemImpl& other) = delete;
		SDL_SoundSystemImpl& operator=(SDL_SoundSystemImpl&& other) = delete;

		void Play(const std::string& path, float volume);

	private:
		// Queue variables
		static const int m_MaxRequests = 10;
		int m_Head = 0;
		int m_Tail = 0;
		std::function<void()> m_pRequests[m_MaxRequests];

		// Mapped sounds
		std::unordered_map<std::string, Mix_Chunk*> m_pSoundEffects;

		// Concurrency variables
		std::mutex m_QueueLock;
		std::condition_variable m_HasRequests;
		std::atomic<bool> m_IsRunning;
		std::jthread m_SoundThread;

		// Sound functions
		void ProcessRequests();
		void PlaySound(const std::string& path, float volume);
};


// Sound System

SDL_SoundSystem::SDL_SoundSystem() {
	pImpl = std::make_unique<SDL_SoundSystemImpl>();
};

SDL_SoundSystem::~SDL_SoundSystem() = default;


void SDL_SoundSystem::Play(const std::string& path, float volume) {
	pImpl->Play(path, volume);
}



// Sound System Impl

SDL_SoundSystem::SDL_SoundSystemImpl::SDL_SoundSystemImpl()
	: m_IsRunning{ true }
	, m_SoundThread{ std::jthread(&SDL_SoundSystem::SDL_SoundSystemImpl::ProcessRequests, this) }
{
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048)) {
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
}

SDL_SoundSystem::SDL_SoundSystemImpl::~SDL_SoundSystemImpl() {
	
	// Free sound effects
	for (auto& effect : m_pSoundEffects) {
		if (effect.second) {
			Mix_FreeChunk(effect.second);
		}
	}

	// Stop thread
	m_IsRunning = false;
	m_HasRequests.notify_all();

	m_SoundThread.join();

	// Quit SDL_mixer
	Mix_Quit();
}

void SDL_SoundSystem::SDL_SoundSystemImpl::ProcessRequests() {
	while (m_IsRunning) {

		// Lock the queue
		std::unique_lock<std::mutex> lk(m_QueueLock);
		if (m_Head == m_Tail && m_IsRunning) {
			m_HasRequests.wait(lk, [&] { return m_Head != m_Tail || !m_IsRunning; });
		}

		if (!m_IsRunning) {
			return;
		}

		// Get the request from the queue
		auto request{ m_pRequests[m_Head] };
		m_Head = (m_Head + 1) % m_MaxRequests;

		lk.unlock();

		// Process event
		request();
	}
}

void SDL_SoundSystem::SDL_SoundSystemImpl::Play(const std::string& path, float volume) {
	
	// Lock the queue
	std::lock_guard<std::mutex> lk(m_QueueLock);

	// No place for requests
	if ((m_Tail + 1) % m_MaxRequests == m_Head) {
		std::cout << "Warning! Audio buffer full!";
		return;
	}

	// Add to queue
	m_pRequests[m_Tail] = std::bind(&SDL_SoundSystem::SDL_SoundSystemImpl::PlaySound, this, path, volume);
	m_Tail = (m_Tail + 1) % m_MaxRequests;

	// Notify condition
	m_HasRequests.notify_all();
}

void SDL_SoundSystem::SDL_SoundSystemImpl::PlaySound(const std::string& path, float volume) {
	
	// Load sound effect if it's not loaded in yet
	if (m_pSoundEffects.find(path) == m_pSoundEffects.end()) {
		m_pSoundEffects[path] = Mix_LoadWAV(path.c_str());
	}

	// Play Sound Effect
	int channel = Mix_PlayChannel(-1, m_pSoundEffects[path], 0);
	Mix_Volume(channel, int(volume* MIX_MAX_VOLUME));
}