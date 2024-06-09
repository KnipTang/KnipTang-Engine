#include "SDLSoundSystem.h"

#include <cassert>
#include <future>
#include <mutex>
#include <SDL_mixer.h>

class dae::SDLSoundSystem::Impl final
{
public:
	Impl(const std::string& dataPath);
	~Impl();

	Impl(const Impl& other) = delete;
	Impl(Impl&& other) = delete;
	Impl& operator=(const Impl& other) = delete;
	Impl& operator=(Impl&& other) = delete;

	void Update();
	
	void play(const std::string name, const int volume, const int loops);
	
	void Stop();

	void Mute();

private:
	void StartSound(Mix_Chunk* soundEffect, const int volume, const int loops);

	std::mutex m_Mutex;
	std::promise<void> m_Promise;
	std::future<void> m_Future;

	bool m_PromiseSet;

	std::string m_dataPath;

	static const int MAX_PENDING = 16;

	PlayMessage pending_[MAX_PENDING];

	int m_Head;
	int m_Tail;

	bool m_Muted;
};

dae::SDLSoundSystem::Impl::Impl(const std::string& dataPath)
{
	m_Future = m_Promise.get_future();
	m_PromiseSet = false;

	m_dataPath = dataPath;
	m_Head = 0;
	m_Tail = 0;

	m_Muted = false;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return;
	}
}

dae::SDLSoundSystem::Impl::~Impl()
{
	Mix_CloseAudio();
}

void dae::SDLSoundSystem::Impl::Update()
{
	m_Future.wait();

	PlayMessage localHead;

	{
		std::lock_guard<std::mutex> lock(m_Mutex);

		if (m_Head == m_Tail) return;

		localHead = pending_[m_Head];

		m_Head = (m_Head + 1) % MAX_PENDING;

		m_Promise = std::promise<void>();
		m_Future = m_Promise.get_future();
		m_PromiseSet = false;
	}

	Mix_Chunk* soundEffect = Mix_LoadWAV(localHead.name.c_str());
	if (!soundEffect)
	{
		std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return;
	}
	StartSound(soundEffect, localHead.volume, localHead.loops);
}

void dae::SDLSoundSystem::Impl::play(const std::string name, const int volume, const int loops)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	std::string path = m_dataPath + name;

	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		if (pending_[i].name == path)
		{
			pending_[i].volume = std::max(volume, pending_[i].volume);
			pending_[i].loops = loops;
			return;
		}
	}

	assert((m_Tail + 1) % MAX_PENDING != m_Head);

	pending_[m_Tail].name = path;
	pending_[m_Tail].volume = volume;
	pending_[m_Tail].loops = loops;
	m_Tail = (m_Tail + 1) % MAX_PENDING;

	if (!m_PromiseSet)
	{
		m_Promise.set_value();
		m_PromiseSet = true;
	}
}

void dae::SDLSoundSystem::Impl::StartSound(Mix_Chunk* soundEffect, const int volume, const int loops)
{
	Mix_VolumeChunk(soundEffect, volume);

	Mix_PlayChannel(-1, soundEffect, loops);
}

void dae::SDLSoundSystem::Impl::Stop()
{
	if (!m_PromiseSet)
	{
		m_Promise.set_value();
		m_PromiseSet = true;
	}
}

void dae::SDLSoundSystem::Impl::Mute()
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	m_Muted = !m_Muted;

	for (int channel = 0; channel < MIX_CHANNELS; ++channel)
	{
		Mix_Volume(channel, m_Muted ? 0 : MIX_MAX_VOLUME);
	}
}

dae::SDLSoundSystem::SDLSoundSystem(const std::string& dataPath)
{
	m_Pimpl = std::make_unique<Impl>(dataPath);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{

}

void dae::SDLSoundSystem::Update()
{
	m_Pimpl.get()->Update();
}

void dae::SDLSoundSystem::play(const std::string name, const int volume, const int loops)
{
	m_Pimpl.get()->play(name, volume, loops);
}

void dae::SDLSoundSystem::Stop()
{
	m_Pimpl.get()->Stop();
}

void dae::SDLSoundSystem::Mute()
{
	m_Pimpl.get()->Mute();
}
