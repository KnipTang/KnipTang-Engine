#pragma once
#include "GameObject.h"

namespace dae
{
	class BaseState
	{
	public:
		BaseState() = default;
		virtual ~BaseState() = default;
	
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete;
	
		virtual void Enter(GameObject*) {}
		virtual void HandleInput(GameObject*) {}
		virtual void Update() {}
	};
}