#include "Triangle.hpp"

#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

Triangle::Triangle() :
    Collision(Collision::TRIANGLE),
    orientation(0)
{
}

Triangle::Triangle(const CGUL::Vector2& position, const CGUL::Vector2& pointA, const CGUL::Vector2& pointB, const CGUL::Vector2& pointC, CGUL::Float32 orientation) :
    Collision(Collision::TRIANGLE),
    position(position),
    pointA(pointA),
    pointB(pointB),
    pointC(pointC),
    orientation(orientation)
{
}

void Triangle::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

CGUL::Vector2 Triangle::GetPosition() const
{
    return position;
}

CGUL::Vector2 Triangle::GetClosestPoint(const CGUL::Vector2& position) const
{
    return position;
}

void Triangle::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    // TODO
}

CGUL::Matrix Triangle::GetWorldMatrix() const
{
    CGUL::Matrix matrix;
    //matrix = matrix * CGUL::Matrix::MakeRotation(orientation);
    matrix = matrix * CGUL::Matrix::MakeTranslation(position);
    return matrix;
}

bool Triangle::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndTriangle(other, *this);
}

bool Triangle::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndTriangle(other, *this);
}

bool Triangle::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckOrientedBoxAndTriangle(other, *this);
}

bool Triangle::CollidingLine(const Line& other) const
{
    return CheckLineAndTriangle(other, *this);
}

bool Triangle::CollidingTriangle(const Triangle& other) const
{
    return CheckTriangleAndTriangle(*this, other);
}

bool Triangle::CollidingPoint(const Point& other) const
{
    return CheckTriangleAndPoint(*this, other);
}

void Triangle::Draw() const
{
    render->Triangle(position, pointA, pointB, pointC, color);
    /*render->Line(position + pointA, position + pointB, color);
    render->Line(position + pointB, position + pointC, color);
    render->Line(position + pointC, position + pointA, color);*/
}
