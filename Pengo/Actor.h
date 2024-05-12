#pragma once
#include <memory>
#include "GameObject.h"

class Actor
{
public:
	Actor() { m_Actor = std::make_unique<dae::GameObject>(); };
	std::unique_ptr<dae::GameObject> GetActor() { return std::move(m_Actor); }

	void HandleInput();
	void Update();
protected:
	std::unique_ptr<dae::GameObject> m_Actor;
};

