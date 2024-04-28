#pragma once
#include <cassert>
#include <iostream>
#include <SDL_mixer.h>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem(const std::string& dataPath);
		~SDLSoundSystem() override;

		void Update() override;

		void play(const std::string name, const int volume) override;

		void Stop() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;
	protected:
		class Impl;
		std::unique_ptr<Impl> m_Pimpl;
	};
}