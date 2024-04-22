#include "ScoreComponent.h"

void dae::ScoreComponent::SetPoints(int points)
{
	m_CurrentPoints = points;

	NotifyObservers(GameEvent::PointsChanged);
}

void dae::ScoreComponent::AddPoints(int points)
{
	m_CurrentPoints += points;

	NotifyObservers(GameEvent::PointsChanged);

	if (m_CurrentPoints >= 500) {
		NotifyObservers(GameEvent::Winner);
	}

}
