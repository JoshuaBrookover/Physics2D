#pragma once
#include <CGUL.hpp>
#include "State.hpp"
#include "Collision.hpp"

struct MovingCircle;

class StateTest : public State
{
    CGUL::Vector< Collision* > objects;
    Collision* drag;
    CGUL::Vector2 offset;
public:
    StateTest();
    ~StateTest();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Exit();
};
