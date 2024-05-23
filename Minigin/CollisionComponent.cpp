#include "CollisionComponent.h"

bool dae::CollisionComponent::Intersects(CollisionComponent& other)
{
    glm::vec3 ownerPos = GetOwner()->GetGameObjectPosition();
    glm::vec3 otherPos = other.GetOwner()->GetGameObjectPosition();

    // Get boundaries of both objects
    float leftA = ownerPos.x;
    float rightA = ownerPos.x + m_Width;
    float topA = ownerPos.y;
    float bottomA = ownerPos.y + m_Height;
    
    float leftB = otherPos.x;
    float rightB = otherPos.x + other.m_Width;
    float topB = otherPos.y;
    float bottomB = otherPos.y + other.m_Height;

    // Check for overlap along both axes
    bool overlapX = leftA < rightB && rightA > leftB;
    bool overlapY = topA < bottomB && bottomA > topB;

    if(overlapX && overlapY)
    {
        NotifyObservers(GameCollisionEvent::Collision, &other);
    }
    else
    {
        NotifyObservers(GameCollisionEvent::NoCollision, &other);
    }

    return overlapX && overlapY;
}
