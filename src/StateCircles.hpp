#pragma once
#include <CGUL.hpp>
#include "State.hpp"
#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

struct MovingCircle;

class StateCircles : public State
{
    CGUL::Vector< MovingCircle* > circles;
public:
    StateCircles();
    ~StateCircles();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Exit();
};
