#include "Collision.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

using namespace CGUL;

void Collision::ProjectionOnAxis(const Vector2* points, const Size count, const Vector2& axis, Float32* min, Float32* max)
{
    Vector2 point = points[0];
    point = points[0];
    Float32 dotProduct = Vector2::DotProduct(axis, point);
    *min = *max = dotProduct;
    for (Byte i = 1; i < count; i++)
    {
        point = points[i];

        dotProduct = Vector2::DotProduct(axis, point);

        if (dotProduct < *min)
        {
            *min = dotProduct;
        }
        if (dotProduct > *max)
        {
            *max = dotProduct;
        }
    }
}

bool Collision::CheckCircleAndCircle(const Circle& a, const Circle& b)
{
    return (Math::Sqr(a.radius + b.radius) > Vector2::DistanceSquared(a.position, b.position));
}

bool Collision::CheckCircleAndAxisAlignedBox(const Circle& circle, const AxisAlignedBox& box)
{
    CGUL::Vector2 closestPoint = box.GetClosestPoint(circle.position);
    return (CGUL::Vector2::DistanceSquared(circle.position, closestPoint) < CGUL::Math::Sqr(circle.radius));
}

bool Collision::CheckCircleAndOrientedBox(const Circle& circle, const OrientedBox& box)
{
    CGUL::Vector2 closestPoint = box.GetClosestPoint(circle.position);
    return (CGUL::Vector2::DistanceSquared(circle.position, closestPoint) < CGUL::Math::Sqr(circle.radius));
}

bool Collision::CheckAxisAlignedBoxAndAxisAlignedBox(const AxisAlignedBox& a, const AxisAlignedBox& b)
{
    CGUL::Vector2 difference = a.position - b.position;
    difference.x = CGUL::Math::Abs(difference.x);
    difference.y = CGUL::Math::Abs(difference.y);
    CGUL::Vector2 combinedExtents = (a.halfExtents + b.halfExtents);

    return (difference.x <= combinedExtents.x && difference.y <= combinedExtents.y);
}

bool Collision::CheckAxisAlignedBoxAndOrientedBox(const AxisAlignedBox& aabb, const OrientedBox& obb)
{
    Vector2 axes[] =
    {
        Vector2::unitX,
        Vector2::unitY,
        Vector2(Math::Cos(obb.orientation), Math::Sin(obb.orientation)),
        Vector2(Math::Sin(obb.orientation), -Math::Cos(obb.orientation))
    };
    return aabb.CollidingOnAxes(obb, axes, 4);
}

bool Collision::CheckOrientedBoxAndOrientedBox(const OrientedBox& a, const OrientedBox& b)
{
    Vector2 axes[] =
    {
        Vector2(Math::Cos(a.orientation), Math::Sin(a.orientation)),
        Vector2(Math::Sin(a.orientation), -Math::Cos(a.orientation)),
        Vector2(Math::Cos(b.orientation), Math::Sin(b.orientation)),
        Vector2(Math::Sin(b.orientation), -Math::Cos(b.orientation))
    };
    return a.CollidingOnAxes(b, axes, 4);
}


Collision::Collision(Enum type) :
    type(type)
{
}

bool Collision::CollidingOnAxis(const Collision& other, const Vector2& axis) const
{
    Float32 min, max, otherMin, otherMax;
    ProjectionOnAxis(axis, &min, &max);
    other.ProjectionOnAxis(axis, &otherMin, &otherMax);

    return (min <= otherMax && max >= otherMin);
}

bool Collision::CollidingOnAxes(const Collision& other, Vector2* axes, Size count) const
{
    for (Size i = 0; i < count; i++)
    {
        if (!CollidingOnAxis(other, axes[i]))
        {
            return false;
        }
    }
    return true;
}
