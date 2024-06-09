#pragma once

namespace dae
{
    enum class GameEvent {
        PlayerDied,
        PointsChanged,
        Winner,
        Collision
    };

    class Subject;
    class Observer
    {
    public:
        Observer() {}
        virtual ~Observer() = default;

        Observer(const Observer& other) = delete;
        Observer(Observer&& other) = delete;
        Observer& operator=(const Observer& other) = delete;
        Observer& operator=(Observer&& other) = delete;

        virtual void Notify(GameEvent event, Subject* actor) = 0;
    };
}
