#include <SDL.h>
#include "InputManager.h"
#include <Xinput.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include <thread>

class dae::InputManager::ControllerPimpl
{
public:
	ControllerPimpl() = default;
	~ControllerPimpl() = default;

	ControllerPimpl(const ControllerPimpl& other) = delete;
	ControllerPimpl(ControllerPimpl&& other) = delete;
	ControllerPimpl& operator=(const ControllerPimpl& other) = delete;
	ControllerPimpl& operator=(ControllerPimpl&& other) = delete;

	bool ProcessInput(float deltaTime)
	{
		for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
			XINPUT_STATE state;
			if (XInputGetState(i, &state) == ERROR_SUCCESS) {
				ProcessControllerInput(i, state, deltaTime);
			}
		}
		return true;
	}

	void BindCommand(DWORD controllerIndex, WORD button, InputActionType inputAction, std::unique_ptr<Command> command)
	{
		controllerBindings[controllerIndex][button] = std::make_pair(inputAction, std::move(command));
	}

private:
	std::unordered_map<DWORD, std::unordered_map<WORD, std::pair<InputActionType, std::unique_ptr<Command>>>> controllerBindings;

	void ProcessControllerInput(DWORD controllerIndex, const XINPUT_STATE& state, float deltaTime)
	{
		XINPUT_STATE& previousState = previousStates[controllerIndex];
		XINPUT_STATE currentState = state;

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		WORD buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		WORD buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

		for (const auto& pair : controllerBindings[controllerIndex]) {
			if (currentState.Gamepad.wButtons & pair.first) {
				switch (pair.second.first)
				{
				case InputActionType::IsDown:
					if (buttonsPressedThisFrame != 0)
						pair.second.second->Execute(deltaTime);
					break;
				case InputActionType::IsUp:
					if (buttonsReleasedThisFrame != 0)
						pair.second.second->Execute(deltaTime);
					break;
				case InputActionType::IsPressed:
					if (currentState.Gamepad.wButtons != 0)
						pair.second.second->Execute(deltaTime);
					break;
				}
			}
		}

		previousStates[controllerIndex] = currentState;
	}

	std::unordered_map<DWORD, XINPUT_STATE> previousStates;
};

dae::InputManager::InputManager() :
	m_Pimpl{ std::make_unique<ControllerPimpl>() }
{

}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.key.keysym.scancode > SDL_NUM_SCANCODES)
			continue;
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			keysPressedThisFrame[e.key.keysym.scancode] = true;
		}
		
		if (e.type == SDL_KEYUP)
		{
			std::fill(std::begin(keysPressedThisFrame), std::end(keysPressedThisFrame), false);
			keysReleasedThisFrame[e.key.keysym.scancode] = true;
		}
	}

	for (auto& [key, binding] : keyBindings)
	{
		if (key > SDL_NUM_SCANCODES)
			continue;

		auto& [inputAction, command] = binding;

		if (inputAction == InputActionType::IsDown && keysPressedThisFrame[key])
			command->Execute(deltaTime);
		else if (inputAction == InputActionType::IsUp && keysReleasedThisFrame[key])
			command->Execute(deltaTime);
		else if (inputAction == InputActionType::IsPressed && keysPressedThisFrame[key])
			command->Execute(deltaTime);
	}

	std::fill(std::begin(keysReleasedThisFrame), std::end(keysReleasedThisFrame), false);

	return m_Pimpl->ProcessInput(deltaTime);
}

void dae::InputManager::BindCommand(DWORD controllerIndex, WORD button, InputActionType inputAction, std::unique_ptr<Command> command)
{
	m_Pimpl->BindCommand(controllerIndex, WORD(button), inputAction, std::move(command));
}

void dae::InputManager::BindCommand(SDL_Scancode key, InputActionType inputAction, std::unique_ptr<Command> command)
{
	keyBindings[key] = std::make_pair(inputAction, std::move(command));
}