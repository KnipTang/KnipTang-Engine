#include "CollisionComponent.h"

bool dae::CollisionComponent::Intersects(CollisionComponent& other)
{
    // Get boundaries of both objects
    float leftA = GetOwner()->GetGameObjectPosition().x;
    float rightA = GetOwner()->GetGameObjectPosition().x + m_Width;
    float topA = GetOwner()->GetGameObjectPosition().y;
    float bottomA = GetOwner()->GetGameObjectPosition().y + m_Height;
    
    float leftB = other.GetOwner()->GetGameObjectPosition().x;
    float rightB = other.GetOwner()->GetGameObjectPosition().x + other.m_Width;
    float topB = other.GetOwner()->GetGameObjectPosition().y;
    float bottomB = other.GetOwner()->GetGameObjectPosition().y + other.m_Height;
    
    // Check for overlap along both axes
    bool overlapX = leftA < rightB && rightA > leftB;
    bool overlapY = topA < bottomB && bottomA > topB;

    // Check for overlap along both axes
    //bool overlapX = std::abs(GetOwner()->GetGameObjectPosition().x - other.GetOwner()->GetGameObjectPosition().x) < (m_Width + other.m_Width) / 2;
    //bool overlapY = std::abs(GetOwner()->GetGameObjectPosition().y - other.GetOwner()->GetGameObjectPosition().y) < (m_Height + other.m_Height) / 2;

    if(overlapX && overlapY)
    {
        NotifyObservers(GameCollisionEvent::Collision, &other);
	    //other.NotifyObservers(GameEvent::Collision);
    }

    return overlapX && overlapY;
}
