#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"
#include <chrono>
namespace dae
{
	class SoundCommand final : public Command {
	public:
		SoundCommand() : Command()
		{
			ss = &SoundServiceLocator::get_sound_system();
		}

		void Execute(float /*deltaTime*/) override
		{
			ss->play("slash.mp3", 10);
		}
	private:
		SoundSystem* ss;
	};
}

