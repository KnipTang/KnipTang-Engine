#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"
#include <chrono>
namespace dae
{
	class SoundMuteCommand final : public Command {
	public:
		SoundMuteCommand() : Command()
		{
			ss = &SoundServiceLocator::get_sound_system();
			ss->Mute();
		}

		void Execute(float /*deltaTime*/) override
		{
			ss->Mute();
		}
	private:
		SoundSystem* ss;
	};
}

