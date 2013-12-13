#include "OrientedBox.hpp"

OrientedBox::OrientedBox() :
    Collision(Collision::ORIENTED_BOX),
    color(0, 0, 0)
{
}

OrientedBox::OrientedBox(const CGUL::Vector2& position, const CGUL::Vector2& halfExtents, CGUL::Float32 orientation) :
    Collision(Collision::ORIENTED_BOX),
    color(0, 0, 0),
    position(position),
    halfExtents(halfExtents),
    orientation(orientation)
{
}

void OrientedBox::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

void OrientedBox::SetHalfExtents(const CGUL::Vector2& halfExtents)
{
    this->halfExtents = halfExtents;
}

void OrientedBox::SetOrientation(CGUL::Float32 orientation)
{
    this->orientation = orientation;
}

CGUL::Vector2 OrientedBox::GetPosition() const
{
    return position;
}

CGUL::Vector2 OrientedBox::GetHalfExtents() const
{
    return halfExtents;
}

CGUL::Float32 OrientedBox::GetOrientation() const
{
    return orientation;
}

void OrientedBox::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Matrix world;
    world = world * CGUL::Matrix::MakeRotation(orientation);

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

bool OrientedBox::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    // TODO
    return false;
}

bool OrientedBox::CollidingOrientedBox(const OrientedBox& other) const
{
    // Note: this logic looks a lot more complicated than it is because of the drawn debug lines

    using namespace CGUL;

    Vector2 axes[] =
    {
        Vector2(Math::Cos(orientation), Math::Sin(orientation)),
        Vector2(Math::Sin(orientation), -Math::Cos(orientation)),
        Vector2(Math::Cos(other.orientation), Math::Sin(other.orientation)),
        Vector2(Math::Sin(other.orientation), -Math::Cos(other.orientation))
    };

    Vector2 average = (position + other.position) / 2.0f;
    for (Size i = 0; i < 4; i++)
    {
        Vector2& axis = axes[i];
        axis.Normalize();

        bool collision = false;
        if (CollidingOnAxis(other, axis))
        {
            collision = true;
        }

        Float32 averageOnAxis;
        averageOnAxis = Vector2::DotProduct(axis, average);

        const OrientedBox* boxes[] = { this, &other };
        for (Size i = 0; i < 2; i++)
        {
            Float32 min, max;
            boxes[i]->ProjectionOnAxis(axis, &min, &max);

            Float32 positionOnAxis;
            positionOnAxis = Vector2::DotProduct(axis, boxes[i]->position);

            Float32 positionMin, positionMax;
            positionMin = min - positionOnAxis;
            positionMax = max - positionOnAxis;

            Float32 averageMin, averageMax;
            averageMin = min - averageOnAxis;
            averageMax = max - averageOnAxis;

            Vector2 p1 = boxes[i]->position + axis * positionMin;
            Vector2 p2 = boxes[i]->position + axis * positionMax;
            render->Line(p1, p2, (collision ? Colors::black : Colors::green));
        }
    }

    return CollidingOnAxes(other, axes, 4);
}

void OrientedBox::Draw() const
{
    render->Box(position, halfExtents * 2, orientation, color);
}
