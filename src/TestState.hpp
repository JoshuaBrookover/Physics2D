#pragma once
#include <CGUL.hpp>
#include "State.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

class TestState : public State
{
    OrientedBox box1;
    OrientedBox box2;
public:
    TestState();
    ~TestState();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Exit();
};
