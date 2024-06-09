#pragma once
#include <iostream>
#include <memory>
#include <chrono>
#include "SoundSystem.h"

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss) : _real_ss(std::move(ss)) {}
		~LoggingSoundSystem() override = default;

		LoggingSoundSystem(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem(LoggingSoundSystem&& other) = delete;
		LoggingSoundSystem& operator=(const LoggingSoundSystem& other) = delete;
		LoggingSoundSystem& operator=(LoggingSoundSystem&& other) = delete;

		void Update() override 
		{
			_real_ss->Update();
		}
		void play(const std::string name, const int volume, const int loops) override {
			_real_ss->play(name, volume, loops);
			std::cout << "playing " << name << " at volume " << volume << " loops " << loops << std::endl;
		}

		void Stop() override { _real_ss->Stop(); };

		void Mute() override { _real_ss->Mute(); };
	};
}
