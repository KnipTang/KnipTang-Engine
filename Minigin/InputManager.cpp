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
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(controllerIndex, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);

		// Handle controller input
		for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
			XINPUT_STATE state;
			if (XInputGetState(i, &state) == ERROR_SUCCESS) {
				WORD buttons = state.Gamepad.wButtons;
				for (const auto& pair : controllerBindings) {
					if (buttons & pair.first) {
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
			}
		}
		return true;
	}

	void BindCommand(WORD button, InputActionType inputAction, std::unique_ptr<Command> command)
	{
		controllerBindings[button] = std::make_pair(inputAction, std::move(command));
	}

private:
	std::unordered_map<WORD, std::pair<InputActionType, std::unique_ptr<Command>>> controllerBindings;

	XINPUT_STATE currentState;
	XINPUT_STATE previousState;
	DWORD controllerIndex;
	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;
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
	const Uint8* previousKeyboardState = SDL_GetKeyboardState(NULL);
	const Uint8* currentKeyboardState = SDL_GetKeyboardState(NULL);

	Uint8 keyboardChanges[SDL_NUM_SCANCODES];
	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
		keyboardChanges[i] = currentKeyboardState[i] ^ previousKeyboardState[i];
	}

	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
		if (keyboardChanges[i] && currentKeyboardState[i]) {
			keysPressedThisFrame[i] = true;
			keysReleasedThisFrame[i] = false;
		}
		else if (keyboardChanges[i] && !currentKeyboardState[i]) {
			keysPressedThisFrame[i] = false;
			keysReleasedThisFrame[i] = true;
		}
		else {
			keysPressedThisFrame[i] = false;
			keysReleasedThisFrame[i] = false;
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
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
	}

	return m_Pimpl->ProcessInput(deltaTime);
}

void dae::InputManager::BindCommand(WORD button, InputActionType inputAction, std::unique_ptr<Command> command)
{
	m_Pimpl->BindCommand(WORD(button), inputAction, std::move(command));
}

void dae::InputManager::BindCommand(int key, InputActionType inputAction, std::unique_ptr<Command> command)
{
	keyBindings[key] = std::make_pair(inputAction, std::move(command));
}