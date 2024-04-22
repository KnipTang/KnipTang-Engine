#pragma once
#include <iostream>

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
        virtual void Notify(GameEvent event, Subject* actor) = 0;
    };
}
