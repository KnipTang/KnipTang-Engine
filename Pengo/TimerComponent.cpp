#include "TimerComponent.h"

#include <iostream>

void TimerComponent::Update(float deltaTime)
{
	m_CurrentTime += deltaTime;
}
