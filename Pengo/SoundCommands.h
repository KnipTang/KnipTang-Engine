#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"

class SoundMuteCommand final : public dae::Command {
public:
	SoundMuteCommand() : Command()
	{
	}
	~SoundMuteCommand() override = default;

	SoundMuteCommand(const SoundMuteCommand& other) = delete;
	SoundMuteCommand(SoundMuteCommand&& other) = delete;
	SoundMuteCommand& operator=(const SoundMuteCommand& other) = delete;
	SoundMuteCommand& operator=(SoundMuteCommand&& other) = delete;

	void Execute(float /*deltaTime*/) override
	{
		dae::SoundServiceLocator::get_sound_system()->Mute();
	}
};
