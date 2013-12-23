#pragma once
#include <CGUL.hpp>
#include "State.hpp"
#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

struct MovingCircle;

class StateTriangulate : public State
{
    CGUL::Vector< CGUL::Vector2 > points;
public:
    StateTriangulate();
    ~StateTriangulate();

    void Enter();
    void Update(CGUL::Float32 deltaTime);
    void Exit();
};
