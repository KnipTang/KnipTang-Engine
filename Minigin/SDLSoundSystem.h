#pragma once
#include <cassert>
#include <iostream>
#include <SDL_mixer.h>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem 
	{
	public:
		SDLSoundSystem()
		{
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
				return;
			}
		}

		void Update() override
		{
			// If there are no pending requests, do nothing.
			if (m_Head == m_Tail) return;

			Mix_Chunk* soundEffect = Mix_LoadWAV(pending_[m_Head].name.c_str());
			if (!soundEffect)
			{
				std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
				return;
			}
			StartSound(soundEffect, pending_[m_Head].volume);

			m_Head = (m_Head + 1) % MAX_PENDING;
		}

		void play(const std::string name, const int volume) override
		{
			std::string path = m_dataPath + name;

			for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
			{
				if (pending_[i].name == path)
				{
					// Use the larger of the two volumes.
					pending_[i].volume = std::max(volume, pending_[i].volume);

					// Don't need to enqueue.
					return;
				}
			}

			assert((m_Tail + 1) % MAX_PENDING != m_Head);
			
			// Add to the end of the list.
			pending_[m_Tail].name = path;
			pending_[m_Tail].volume = volume;
			m_Tail = (m_Tail + 1) % MAX_PENDING;
		}

		void StartSound(Mix_Chunk* soundEffect, const int volume)
		{
			// Set the volume of the sound effect
			Mix_VolumeChunk(soundEffect, volume);

			// Play the sound effect once
			Mix_PlayChannel(-1, soundEffect, 0);
		}
	};
}