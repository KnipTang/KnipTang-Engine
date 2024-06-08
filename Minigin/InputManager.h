#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <SDL.h>
#include "InputManager.h"
#define NOMINMAX
#include <Windows.h>
#include <Xinput.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include <memory>
namespace dae
{
	enum class InputActionType {
		IsDown,
		IsUp,
		IsPressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		void BindCommand(int key, InputActionType inputAction, std::unique_ptr<Command> command);
		void BindCommand(DWORD controllerIndex, WORD button, InputActionType inputAction, std::unique_ptr<Command> command);

		bool ProcessInput(float deltaTime);
	private:
		class ControllerPimpl;
		std::unique_ptr<ControllerPimpl> m_Pimpl;

		std::unordered_map<int, std::pair<InputActionType, std::unique_ptr<Command>>> keyBindings;
		bool keysPressedThisFrame[SDL_NUM_SCANCODES] = { false };
		bool keysReleasedThisFrame[SDL_NUM_SCANCODES] = { false };
	};

}
