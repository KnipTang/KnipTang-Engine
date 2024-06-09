#pragma once
#include <iostream>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem : public SoundSystem
	{
	public:
		SDLSoundSystem(const std::string& dataPath);
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		void Update() override;

		void play(const std::string name, const int volume, const int loops) override;

		void Stop() override;

		void Mute() override;
	protected:
		class Impl;
		std::unique_ptr<Impl> m_Pimpl;
	};
}