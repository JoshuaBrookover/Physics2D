#pragma once
#include <CGUL.hpp>

class State;
class Render;

extern Render* render;

class StateMachine
{
    static void KeyButtonEvent(const CGUL::WindowKeyButtonEvent& event);
    static void MouseButtonEvent(const CGUL::WindowMouseButtonEvent& event);
    static void MouseMoveEvent(const CGUL::WindowMouseMoveEvent& event);

    State* currentState;
    State* queuedState;

    CGUL::Window window;
    CGUL::Timer timer;

    CGUL::SCoord32 mousePosition;
public:
    StateMachine();
    ~StateMachine();

    void ChangeState(State* newState);

    void Initialize();
    bool IsRunning() const;
    void Update();
    void Reset();
    void Exit();

    CGUL::SCoord32 GetMousePosition() const;
};
