#include "CollisionComponent.h"

bool dae::CollisionComponent::Intersects(CollisionComponent& other)
{
    // Check for overlap along both axes
    bool overlapX = std::abs(GetOwner()->GetGameObjectPosition().x - other.GetOwner()->GetGameObjectPosition().x) < (m_Width + other.m_Width) / 2;
    bool overlapY = std::abs(GetOwner()->GetGameObjectPosition().y - other.GetOwner()->GetGameObjectPosition().y) < (m_Height + other.m_Height) / 2;

    if(overlapX && overlapY)
    {
        NotifyObservers(GameEvent::Collision, &other);
	    //other.NotifyObservers(GameEvent::Collision);
    }

    return overlapX && overlapY;
}
