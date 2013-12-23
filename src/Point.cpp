#include "Point.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

Point::Point() :
    Collision(Collision::POINT)
{
}

Point::Point(const CGUL::Vector2& position) :
    Collision(Collision::POINT),
    position(position)
{
}

void Point::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

CGUL::Vector2 Point::GetPosition() const
{
    return this->position;
}

CGUL::Vector2 Point::GetClosestPoint(const CGUL::Vector2& position) const
{
    return position;
}

CGUL::Matrix Point::GetWorldMatrix() const
{
    return CGUL::Matrix();
}

void Point::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    *min = *max = CGUL::Vector2::DotProduct(axis, this->position);
}

bool Point::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndPoint(other, *this);
}

bool Point::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndPoint(other, *this);
}

bool Point::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckOrientedBoxAndPoint(other, *this);
}

bool Point::CollidingLine(const Line& other) const
{
    return CheckLineAndPoint(other, *this);
}

bool Point::CollidingTriangle(const Triangle& other) const
{
    return CheckTriangleAndPoint(other, *this);
}

bool Point::CollidingPoint(const Point& other) const
{
    return CheckPointAndPoint(*this, other);
}

void Point::Draw() const
{
}
