#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"
#include <chrono>

class SoundMuteCommand final : public dae::Command {
public:
	SoundMuteCommand() : Command()
	{
	}

	void Execute(float /*deltaTime*/) override
	{
		dae::SoundServiceLocator::get_sound_system()->Mute();
	}
private:
};


