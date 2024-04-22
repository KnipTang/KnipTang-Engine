#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <SDL.h>
#include "InputManager.h"
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
		void BindCommand(WORD button, InputActionType inputAction, std::unique_ptr<Command> command);

		bool ProcessInput(float deltaTime);
	private:
		class ControllerPimpl;
		ControllerPimpl* m_pimpleControlClass;
	};

}
