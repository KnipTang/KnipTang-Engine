#pragma once
#include <memory>
#include "GameObject.h"
#include "PengoState.h"


class PengoPlayer
{
public:
	PengoPlayer();
	std::unique_ptr<dae::GameObject> GetPlayer() { return std::move(m_Player); }

	void HandleInput(Controlls control);
private:
	std::unique_ptr<dae::GameObject> m_Player;

	PengoState* m_State;
};

