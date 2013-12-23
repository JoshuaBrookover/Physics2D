#include "AxisAlignedBox.hpp"

#include "Circle.hpp"
#include "OrientedBox.hpp"
#include "Line.hpp"
#include "Point.hpp"

AxisAlignedBox::AxisAlignedBox() :
    Collision(Collision::AXIS_ALIGNED_BOX)
{
}

AxisAlignedBox::AxisAlignedBox(const CGUL::Vector2& position, const CGUL::Vector2& halfExtents) :
    Collision(Collision::AXIS_ALIGNED_BOX),
    position(position),
    halfExtents(halfExtents)
{
}

void AxisAlignedBox::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void AxisAlignedBox::SetHalfExtents(const CGUL::Vector2& halfExtents)
{
    this->halfExtents = halfExtents;
}

CGUL::Vector2 AxisAlignedBox::GetPosition() const
{
    return this->position;
}

CGUL::Vector2 AxisAlignedBox::GetExtents() const
{
    return this->halfExtents;
}

CGUL::Vector2 AxisAlignedBox::GetClosestPoint(const CGUL::Vector2& position) const
{
    using namespace CGUL;

    Vector2 difference = position - this->position;
    difference.x = Math::Clamp(difference.x, -halfExtents.x, halfExtents.x);
    difference.y = Math::Clamp(difference.y, -halfExtents.y, halfExtents.y);
    return this->position + difference;
}

CGUL::Matrix AxisAlignedBox::GetWorldMatrix() const
{
    return CGUL::Matrix::MakeTranslation(position);
}

void AxisAlignedBox::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Matrix world;
    world = world * CGUL::Matrix::MakeTranslation(position);

    CGUL::Vector2 points[] =
    {
        CGUL::Vector2( halfExtents.x,  halfExtents.y) * world,
        CGUL::Vector2(-halfExtents.x,  halfExtents.y) * world,
        CGUL::Vector2( halfExtents.x, -halfExtents.y) * world,
        CGUL::Vector2(-halfExtents.x, -halfExtents.y) * world
    };

    return Collision::ProjectionOnAxis(points, 4, axis, min, max);
}

bool AxisAlignedBox::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndAxisAlignedBox(other, *this);
}

bool AxisAlignedBox::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndAxisAlignedBox(*this, other);
}

bool AxisAlignedBox::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckAxisAlignedBoxAndOrientedBox(*this, other);
}

bool AxisAlignedBox::CollidingLine(const Line& other) const
{
    return CheckAxisAlignedBoxAndLine(*this, other);
}

bool AxisAlignedBox::CollidingTriangle(const Triangle& other) const
{
    return CheckAxisAlignedBoxAndTriangle(*this, other);
}

bool AxisAlignedBox::CollidingPoint(const Point& other) const
{
    return CheckAxisAlignedBoxAndPoint(*this, other);
}

void AxisAlignedBox::Draw() const
{
    render->Box(position, halfExtents * 2, color);
}
