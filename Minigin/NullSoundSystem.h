#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		NullSoundSystem() = default;
		~NullSoundSystem() override;
		void Update() override {}
		void play(const std::string name, const int, const int) override;
		void Stop() override {};
		void Mute() override {};

		NullSoundSystem(const NullSoundSystem& other) = delete;
		NullSoundSystem(NullSoundSystem&& other) = delete;
		NullSoundSystem& operator=(const NullSoundSystem& other) = delete;
		NullSoundSystem& operator=(NullSoundSystem&& other) = delete;
	};
}
