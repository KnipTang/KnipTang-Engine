#include "SoundServiceLocator.h"

std::unique_ptr<dae::SoundSystem> dae::SoundServiceLocator::_ss_instance{ std::make_unique<dae::NullSoundSystem>() };
