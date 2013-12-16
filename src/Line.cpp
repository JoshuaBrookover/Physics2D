#include "Line.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

Line::Line() :
    Collision(Collision::LINE),
    color(0, 0, 0)
{
}

Line::Line(const CGUL::Vector2& start, const CGUL::Vector2& end) :
    Collision(Collision::LINE),
    color(0, 0, 0),
    start(start),
    end(end)
{
}

void Line::SetStart(const CGUL::Vector2& start)
{
    this->start = start;
}

void Line::SetEnd(const CGUL::Vector2& end)
{
    this->end = end;
}

CGUL::Vector2 Line::GetStart() const
{
    return this->start;
}

CGUL::Vector2 Line::GetEnd() const
{
    return this->end;
}

CGUL::Vector2 Line::GetClosestPoint(const CGUL::Vector2& position) const
{
    // TODO
    return position;
}

void Line::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    // TODO
}

bool Line::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndLine(other, *this);
}

bool Line::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndLine(other, *this);
}

bool Line::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckOrientedBoxAndLine(other, *this);
}

bool Line::CollidingLine(const Line& other) const
{
    return CheckLineAndLine(*this, other);
}

void Line::Draw() const
{
    render->Line(start, end, color);
}
