#pragma once
#include <memory>
#include "SoundSystem.h"
#include "NullSoundSystem.h"
namespace dae
{
	class SoundServiceLocator final
	{
		static std::unique_ptr<SoundSystem> _ss_instance;
	public:
		static SoundSystem& get_sound_system() { return *_ss_instance; }
		static void register_sound_system(std::unique_ptr<SoundSystem>&& ss) {
			_ss_instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}