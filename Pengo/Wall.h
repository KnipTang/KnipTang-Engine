#pragma once
#include "Actor.h"

class Wall
{
public:
	Wall(int posX, int posY);
	std::unique_ptr<dae::GameObject> m_Actor;
private:
};

