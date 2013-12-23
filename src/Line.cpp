#include "Line.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

Line::Line() :
    Collision(Collision::LINE)
{
}

Line::Line(const CGUL::Vector2& start, const CGUL::Vector2& end) :
    Collision(Collision::LINE),
    start(start),
    end(end)
{
}

void Line::SetPosition(const CGUL::Vector2& position)
{
    this->start = position;
}

void Line::SetStart(const CGUL::Vector2& start)
{
    this->start = start;
}

void Line::SetEnd(const CGUL::Vector2& end)
{
    this->end = end;
}

CGUL::Vector2 Line::GetPosition() const
{
    return this->start;
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
    using namespace CGUL;

    Vector2 axis = this->end - this->start;
    axis.Normalize();
    Vector2 perp(axis.y, -axis.x);

    Float32 axisPosition = Vector2::DotProduct(position, axis);
    Float32 axisMin = Vector2::DotProduct(start, axis);
    Float32 axisMax = Vector2::DotProduct(end, axis);
    axisPosition = Math::Clamp(axisPosition, axisMin, axisMax);

    Float32 perpPosition = Vector2::DotProduct(start, perp);

    return axis * axisPosition + perp * perpPosition;
}

CGUL::Matrix Line::GetWorldMatrix() const
{
    // TODO
    return CGUL::Matrix();
}

void Line::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Matrix world;

    CGUL::Vector2 points[] =
    {
        start, end
    };

    return Collision::ProjectionOnAxis(points, 2, axis, min, max);
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

bool Line::CollidingTriangle(const Triangle& other) const
{
    return CheckLineAndTriangle(*this, other);
}

bool Line::CollidingPoint(const Point& other) const
{
    return CheckLineAndPoint(*this, other);
}

void Line::Draw() const
{
    render->Line(start, end, color);
}
