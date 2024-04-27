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
        void Render() const override {}

        void SetSize(float width, float height) 
        { 
            m_Width = width;
            m_Height = height;
        }
        glm::vec2 GetSize() { return glm::vec2{m_Width, m_Height }; }
        // Function to check for collision with another rectangle
        bool Intersects(const CollisionComponent& other);
    private:
        float m_Width{};
        float m_Height{};
    };
}

