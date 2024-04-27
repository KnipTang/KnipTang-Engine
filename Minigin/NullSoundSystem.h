#pragma once
#include <memory>

#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	public:
		~NullSoundSystem() override;
		void Update() override {}
		void play(const std::string name, const int) override;
	};
}
