#pragma once
#include <CGUL.hpp>
#include "Render.hpp"
#include "StateMachine.hpp"

class State
{
protected:
    StateMachine* stateMachine;
    Render* render;

    CGUL::Window* window;
public:
    State();
    ~State();

    void Setup(StateMachine* stateMachine, Render* render, CGUL::Window* window);

    virtual void Enter() = 0;
    virtual void Update(CGUL::Float32 deltaTime) = 0;
    virtual void Draw() const = 0;
    virtual void Exit() = 0;
};
