#include "Circle.hpp"

#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"
#include "Line.hpp"

Circle::Circle() :
    Collision(Collision::CIRCLE),
    radius(0),
    orientation(0)
{
}

Circle::Circle(const CGUL::Vector2& position, CGUL::Float32 radius, CGUL::Float32 orientation) :
    Collision(Collision::CIRCLE),
    position(position),
    radius(radius),
    orientation(orientation)
{
}

void Circle::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void Circle::SetRadius(CGUL::Float32 radius)
{
    this->radius = radius;
}

CGUL::Vector2 Circle::GetPosition() const
{
    return position;
}

CGUL::Float32 Circle::GetRadius() const
{
    return radius;
}

CGUL::Vector2 Circle::GetClosestPoint(const CGUL::Vector2& position) const
{
    CGUL::Vector2 difference = position - this->position;
    CGUL::Float32 distance = difference.GetMagnitude();
    if (distance > radius)
    {
        difference /= distance;
        difference *= radius;
        return this->position + difference;
    }
    return position;
}

CGUL::Matrix Circle::GetWorldMatrix() const
{
    CGUL::Matrix matrix;
    matrix = matrix * CGUL::Matrix::MakeRotation(orientation);
    matrix = matrix * CGUL::Matrix::MakeTranslation(position);
    return matrix;
}

void Circle::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Float32 projection = CGUL::Vector2::DotProduct(axis, position);
    *min = projection - radius;
    *max = projection + radius;
}

bool Circle::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndCircle(*this, other);
}

bool Circle::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckCircleAndAxisAlignedBox(*this, other);
}

bool Circle::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckCircleAndOrientedBox(*this, other);
}

bool Circle::CollidingLine(const Line& other) const
{
    return CheckCircleAndLine(*this, other);
}

bool Circle::CollidingTriangle(const Triangle& other) const
{
    return CheckCircleAndTriangle(*this, other);
}

bool Circle::CollidingPoint(const Point& other) const
{
    return CheckCircleAndPoint(*this, other);
}

void Circle::Draw() const
{
    render->Circle(position, radius, orientation, color);
}
