#include "AxisAlignedBox.hpp"

AxisAlignedBox::AxisAlignedBox() :
    color(0, 0, 0)
{
}

AxisAlignedBox::AxisAlignedBox(const CGUL::Vector2& position, const CGUL::Vector2& extents) :
    color(0, 0, 0),
    position(position),
    extents(extents)
{
}

void AxisAlignedBox::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void AxisAlignedBox::SetExtents(const CGUL::Vector2& extents)
{
    this->extents = extents;
}

CGUL::Vector2 AxisAlignedBox::GetPosition() const
{
    return this->position;
}

CGUL::Vector2 AxisAlignedBox::GetExtents() const
{
    return this->extents;
}

bool AxisAlignedBox::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    render->Line(position, other.position, CGUL::Colors::red);

    CGUL::Vector2 difference = position - other.position;
    difference.x = CGUL::Math::Abs(difference.x);
    difference.y = CGUL::Math::Abs(difference.y);
    CGUL::Vector2 combinedExtents = (extents + other.extents) / 2;

    return (difference.x <= combinedExtents.x && difference.y <= combinedExtents.y);
}

bool AxisAlignedBox::CollidingOrientedBox(const OrientedBox& other) const
{
    return false; // TODO
}

void AxisAlignedBox::Draw() const
{
    render->Box(position, extents, color);
}
