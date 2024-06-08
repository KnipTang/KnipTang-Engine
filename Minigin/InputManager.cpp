#include <SDL.h>
#include "InputManager.h"
#include <Xinput.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include <thread>

class dae::InputManager::ControllerPimpl
{
public:
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

	//const Uint8* previousKeyboardState = SDL_GetKeyboardState(NULL);
	//const Uint8* currentKeyboardState = SDL_GetKeyboardState(NULL);

	//Uint8 keyboardChanges[SDL_NUM_SCANCODES];
	//for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
	//	keyboardChanges[i] = currentKeyboardState[i] ^ previousKeyboardState[i];
	//}
	//
	//for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
	//	if (keyboardChanges[i] && currentKeyboardState[i]) {
	//		keysPressedThisFrame[i] = true;
	//		keysReleasedThisFrame[i] = false;
	//	}
	//	else if (keyboardChanges[i] && !currentKeyboardState[i]) {
	//		keysPressedThisFrame[i] = false;
	//		keysReleasedThisFrame[i] = true;
	//	}
	//	else {
	//		keysPressedThisFrame[i] = false;
	//		keysReleasedThisFrame[i] = false;
	//	}
	//}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.key.keysym.sym > SDL_NUM_SCANCODES)
			continue;
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN /* && !e.key.repeat*/)
		{
			keysPressedThisFrame[e.key.keysym.sym] = true;
		}
		
		if (e.type == SDL_KEYUP)
		{
			std::fill(std::begin(keysPressedThisFrame), std::end(keysPressedThisFrame), false);
			keysReleasedThisFrame[e.key.keysym.sym] = true;
		}

		/*
		if (e.type == SDL_KEYDOWN)
		{
			int keyCode = e.key.keysym.sym;
			auto it = keyBindings.find(keyCode);
			if (it != keyBindings.end())
			{
				switch (it->second.first)
				{
				case InputActionType::IsDown:
					if (!keysPressedThisFrame[it->first])
						it->second.second->Execute(deltaTime);
					break;
				case InputActionType::IsUp:
					if (keysReleasedThisFrame[it->first])
						it->second.second->Execute(deltaTime);
					break;
				case InputActionType::IsPressed:
					it->second.second->Execute(deltaTime);
					break;
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			int keyCode = e.key.keysym.sym;
			auto it = keyBindings.find(keyCode);
			if (it != keyBindings.end())
			{
				switch (it->second.first)
				{
				case InputActionType::IsUp:
					if (!keysReleasedThisFrame[it->first])
						it->second.second->Execute(deltaTime);
					break;
				}
			}
		}
		*/
	}

	//const Uint8* state = SDL_GetKeyboardState(NULL);

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

void dae::InputManager::BindCommand(int key, InputActionType inputAction, std::unique_ptr<Command> command)
{
	keyBindings[key] = std::make_pair(inputAction, std::move(command));
}