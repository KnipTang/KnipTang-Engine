#pragma once
#include <cmath>
#define NOMINMAX
#include <windows.h>
#include <windef.h>
#include <glm/vec2.hpp>

#include "Component.h"
#include "GameObject.h"
#include "Subject.h"
namespace dae
{
    class CollisionComponent : public Component, public Subject
    {
    public:
        CollisionComponent(GameObject* gameObject, float width, float height)
            : Component(gameObject), Subject(gameObject), m_Width(width), m_Height(height)
        { }

        void Update(float /*deltaTime*/) override {}
        void LateUpdate(float /*deltaTime*/) override {}
        void FixedUpdate(float /*fixedTimeStep*/) override {}
        void Render() const override
        {
#if NDEBUG
#else
            // Get the position of the game object
            glm::vec2 position = GetOwner()->GetGameObjectPosition();
            // Create a rectangle representing the collider
            RECT rect;
            rect.left = static_cast<LONG>(position.x - m_Width / 2);
            rect.top = static_cast<LONG>(position.y - m_Height / 2);
            rect.right = static_cast<LONG>(position.x + m_Width / 2);
            rect.bottom = static_cast<LONG>(position.y + m_Height / 2);
            // Get the device context
            HDC hdc = GetDC(nullptr);
            // Draw the rectangle
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            // Release the device context
            ReleaseDC(nullptr, hdc);
#endif
        }

        void NotifyObservers(GameEvent event, CollisionComponent* other) {
            for (const auto& observer : GetObservers())
                observer->Notify(event, other);
        }

        void SetSize(float width, float height) 
        { 
            m_Width = width;
            m_Height = height;
        }
        glm::vec2 GetSize() { return glm::vec2{m_Width, m_Height }; }
        // Function to check for collision with another rectangle
        bool Intersects(CollisionComponent& other);
    private:
        float m_Width{};
        float m_Height{};
    };
}

