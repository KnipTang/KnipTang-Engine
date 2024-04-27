#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"

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
			ss->play("Death.wav", 10);
		}
	private:
		SoundSystem* ss;
	};
}

