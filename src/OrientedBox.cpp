#include "OrientedBox.hpp"

OrientedBox::OrientedBox() :
    color(0, 0, 0)
{
}

OrientedBox::OrientedBox(const CGUL::Vector2& position, const CGUL::Vector2& extents, CGUL::Float32 orientation) :
    color(0, 0, 0),
    position(position),
    extents(extents),
    orientation(orientation)
{
}

void OrientedBox::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void OrientedBox::SetExtents(const CGUL::Vector2& extents)
{
    this->extents = extents;
}

void OrientedBox::SetOrientation(CGUL::Float32 orientation)
{
    this->orientation = orientation;
}

CGUL::Vector2 OrientedBox::GetPosition() const
{
    return position;
}

CGUL::Vector2 OrientedBox::GetExtents() const
{
    return extents;
}

CGUL::Float32 OrientedBox::GetOrientation() const
{
    return orientation;
}

bool OrientedBox::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    // TODO
    return false;
}

bool OrientedBox::CollidingOrientedBox(const OrientedBox& other) const
{
    // TODO
    return false;
}

void OrientedBox::Draw() const
{
    render->Box(position, extents, orientation, color);
}
