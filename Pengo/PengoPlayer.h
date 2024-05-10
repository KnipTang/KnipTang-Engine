#pragma once
#include <memory>
#include "GameObject.h"
#include "PengoState.h"
#include "Actor.h"

class PengoPlayer : public Actor
{
public:
	PengoPlayer(int posX, int posY);
	~PengoPlayer() { m_State = nullptr; delete m_State; }

	void HandleInput(Controlls control);
private:

	PengoState* m_State;
};

