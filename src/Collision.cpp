#include "Collision.hpp"

#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "Point.hpp"

using namespace CGUL;

void Collision::ProjectionOnAxis(const Vector2* points, const Size count, const Vector2& axis, Float32* min, Float32* max)
{
    Vector2 point = points[0];
    point = points[0];
    Float32 dotProduct = Vector2::DotProduct(axis, point);
    *min = *max = dotProduct;
    for (Size i = 1; i < count; i++)
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

bool Collision::CheckCircleAndLine(const Circle& circle, const Line& line)
{
    CGUL::Vector2 closestPoint = line.GetClosestPoint(circle.position);
    return (CGUL::Vector2::DistanceSquared(circle.position, closestPoint) < CGUL::Math::Sqr(circle.radius));
}

bool Collision::CheckCircleAndTriangle(const Circle& circle, const Triangle& triangle)
{
    CGUL::Vector2 closestPoint = triangle.GetClosestPoint(circle.position);
    return (CGUL::Vector2::DistanceSquared(circle.position, closestPoint) < CGUL::Math::Sqr(circle.radius));
}

bool Collision::CheckCircleAndPoint(const Circle& circle, const Point& point)
{
    // TODO
    return false;
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

bool Collision::CheckAxisAlignedBoxAndLine(const AxisAlignedBox& box, const Line& line)
{
    // TODO
    return false;
}

bool Collision::CheckAxisAlignedBoxAndTriangle(const AxisAlignedBox& box, const Triangle& triangle)
{
    Vector2 side1 = triangle.pointA - triangle.pointB;
    Vector2 side2 = triangle.pointB - triangle.pointC;
    Vector2 side3 = triangle.pointC - triangle.pointA;

    Vector2 axes[] =
    {
        Vector2::unitX,
        Vector2::unitY,
        Vector2::Normalized(side1.GetPerpendicular()),
        Vector2::Normalized(side2.GetPerpendicular()),
        Vector2::Normalized(side3.GetPerpendicular())
    };
    return box.CollidingOnAxes(triangle, axes, 5);
}

bool Collision::CheckAxisAlignedBoxAndPoint(const AxisAlignedBox& box, const Point& point)
{
    // TODO
    return false;
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

bool Collision::CheckOrientedBoxAndLine(const OrientedBox& box, const Line& line)
{
    // TODO
    return false;
}

bool Collision::CheckOrientedBoxAndTriangle(const OrientedBox& box, const Triangle& triangle)
{
    Vector2 side1 = triangle.pointA - triangle.pointB;
    Vector2 side2 = triangle.pointB - triangle.pointC;
    Vector2 side3 = triangle.pointC - triangle.pointA;

    Vector2 axes[] =
    {
        Vector2(Math::Cos(box.orientation), Math::Sin(box.orientation)),
        Vector2(Math::Sin(box.orientation), -Math::Cos(box.orientation)),
        Vector2::Normalized(side1.GetPerpendicular()),
        Vector2::Normalized(side2.GetPerpendicular()),
        Vector2::Normalized(side3.GetPerpendicular())
    };
    return box.CollidingOnAxes(triangle, axes, 5);
}

bool Collision::CheckOrientedBoxAndPoint(const OrientedBox& box, const Point& point)
{
    // TODO
    return false;
}

bool Collision::CheckLineAndLine(const Line& a, const Line& b)
{
    // TODO
    return false;
}

bool Collision::CheckLineAndTriangle(const Line& line, const Triangle& triangle)
{
    // TODO
    return false;
}

bool Collision::CheckLineAndPoint(const Line& line, const Point& point)
{
    // TODO
    return false;
}

bool Collision::CheckTriangleAndTriangle(const Triangle& a, const Triangle& b)
{
    // TODO
    return false;
}

bool Collision::CheckTriangleAndPoint(const Triangle& triangle, const Point& point)
{
    Vector2 p = point.position, a = triangle.pointA, b = triangle.pointB, c = triangle.pointC;
    float pab = Vector2::CrossProduct(p - a, b - a);
    float pbc = Vector2::CrossProduct(p - b, c - b);
    if (Math::Sign(pab) != Math::Sign(pbc))
    {
        return false;
    }
    float pca = Vector2::CrossProduct(p - c, a - c);
    if (Math::Sign(pab) != Math::Sign(pca))
    {
        return false;
    }
    return true;
}

bool Collision::CheckPointAndPoint(const Point& a, const Point& b)
{
    return (a.position == b.position);
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

bool Collision::Colliding(const Collision* other) const
{
    switch (type)
    {
        case CIRCLE: return other->CollidingCircle(*(Circle*)this);
        case AXIS_ALIGNED_BOX: return other->CollidingAxisAlignedBox(*(AxisAlignedBox*)this);
        case ORIENTED_BOX: return other->CollidingOrientedBox(*(OrientedBox*)this);
        case LINE: return other->CollidingLine(*(Line*)this);
        default: return false;
    }
}
