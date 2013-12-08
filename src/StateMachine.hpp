#pragma once
#include <CGUL.hpp>

class State;
class Render;

class StateMachine
{
    State* currentState;
    State* queuedState;

    Render* render;

    CGUL::Window window;
    CGUL::Timer timer;
public:
    StateMachine();
    ~StateMachine();

    void ChangeState(State* newState);

    void Initialize();
    bool IsRunning() const;
    void Update();
    void Reset();
    void Exit();
};
