#pragma once
#define NOMINMAX
#include <glm/vec2.hpp>
#include "CollisionObserver.h"
#include "Component.h"
#include "GameObject.h"
#include <memory>

namespace dae
{
    class CollisionComponent : public Component
    {
    public:
        CollisionComponent(GameObject* gameObject, float width, float height, float left = 0, float top = 0)
            : Component(gameObject), m_Width(width), m_Height(height), m_Left(left), m_Top(top)
        { }
    	~CollisionComponent() override = default;

        CollisionComponent(const CollisionComponent& other) = delete;
        CollisionComponent(CollisionComponent&& other) = delete;
        CollisionComponent& operator=(const CollisionComponent& other) = delete;
        CollisionComponent& operator=(CollisionComponent&& other) = delete;

        void SetSize(float width, float height) 
        { 
            m_Width = width;
            m_Height = height;
        }
        glm::vec2 GetSize() { return glm::vec2{m_Width, m_Height }; }

        bool Intersects(CollisionComponent& other);

        void AddObserver(CollisionObserver* observer) {
            m_observers.push_back(std::unique_ptr<CollisionObserver>(observer));
        }
        void RemoveObserver(CollisionObserver* observer) {
            auto it = std::find_if(m_observers.begin(), m_observers.end(),
                [&observer](const std::unique_ptr<CollisionObserver>& ptr) { return ptr.get() == observer; });
        
            if (it != m_observers.end()) {
                m_observers.erase(it);
            }
        }

        void NotifyObservers(GameCollisionEvent event, CollisionComponent* other) {
            for (const auto& observer : m_observers)
                observer->NotifyCollision(event, other);
        }

        size_t GetObserversCount() const { return m_observers.size(); }
        CollisionObserver* GetObserverAt(unsigned int index) const { return m_observers.at(index).get(); }

    private:
        float m_Width{};
        float m_Height{};
        float m_Left{};
        float m_Top{};
        std::vector<std::unique_ptr<CollisionObserver>> m_observers;
    };
}

