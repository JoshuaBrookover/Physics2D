#pragma once
#include <CGUL.hpp>
#include "State.hpp"

class TestState : public State
{
public:
    TestState();
    ~TestState();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Draw() const;
    void Exit();
};
