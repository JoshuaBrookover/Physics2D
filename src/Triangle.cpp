#include "Triangle.hpp"

#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"

Triangle::Triangle() :
    Collision(Collision::TRIANGLE),
    orientation(0)
{
}

Triangle::Triangle(const CGUL::Vector2& position, const CGUL::Vector2& pointA, const CGUL::Vector2& pointB, const CGUL::Vector2& pointC, CGUL::Float32 orientation) :
    Collision(Collision::TRIANGLE),
    position(position),
    pointA(pointA),
    pointB(pointB),
    pointC(pointC),
    orientation(orientation)
{
}

void Triangle::SetPosition(const CGUL::Vector2& position)
{
    this->position = position;
}

CGUL::Vector2 Triangle::GetPosition() const
{
    return position;
}

CGUL::Vector2 Triangle::GetClosestPoint(const CGUL::Vector2& position) const
{
    using namespace CGUL;

    Vector2 axes[] =
    {
        Vector2::Normalized(pointA - pointB),
        Vector2::Normalized(pointB - pointC),
        Vector2::Normalized(pointC - pointA)
    };

    Vector2 points[3][2] =
    {
        { pointA, pointB },
        { pointB, pointC },
        { pointC, pointA }
    };

    Vector2 result = position - this->position;
    for (Byte i = 0; i < 3; i++)
    {
        Vector2 axis = axes[i];
        Vector2 perp = axis.GetPerpendicular();

        Float32 positionOnAxis = Vector2::DotProduct(result, axis);
        Float32 positionOnPerp = Vector2::DotProduct(result, perp);
        Float32 pointOnPerp = Vector2::DotProduct(points[i][0], perp);

        if (pointOnPerp > positionOnPerp)
        {
            positionOnPerp = pointOnPerp;
        }

        Float32 min, max, projection;
        min = max = Vector2::DotProduct(axis, pointA);
        projection = Vector2::DotProduct(axis, pointB);
        min = Math::Min(min, projection);
        max = Math::Max(max, projection);
        projection = Vector2::DotProduct(axis, pointC);
        min = Math::Min(min, projection);
        max = Math::Max(max, projection);
        positionOnAxis = Math::Clamp(positionOnAxis, min, max);

        result = axis * positionOnAxis + perp * positionOnPerp;
    }

    //return this->position + result;
    return this->position + result;
}

void Triangle::ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const
{
    CGUL::Matrix world;
    world = world * CGUL::Matrix::MakeTranslation(position);

    CGUL::Vector2 points[] =
    {
        pointA * world,
        pointB * world,
        pointC * world
    };

    return Collision::ProjectionOnAxis(points, 3, axis, min, max);
}

CGUL::Matrix Triangle::GetWorldMatrix() const
{
    CGUL::Matrix matrix;
    //matrix = matrix * CGUL::Matrix::MakeRotation(orientation);
    matrix = matrix * CGUL::Matrix::MakeTranslation(position);
    return matrix;
}

bool Triangle::CollidingCircle(const Circle& other) const
{
    return CheckCircleAndTriangle(other, *this);
}

bool Triangle::CollidingAxisAlignedBox(const AxisAlignedBox& other) const
{
    return CheckAxisAlignedBoxAndTriangle(other, *this);
}

bool Triangle::CollidingOrientedBox(const OrientedBox& other) const
{
    return CheckOrientedBoxAndTriangle(other, *this);
}

bool Triangle::CollidingLine(const Line& other) const
{
    return CheckLineAndTriangle(other, *this);
}

bool Triangle::CollidingTriangle(const Triangle& other) const
{
    return CheckTriangleAndTriangle(*this, other);
}

bool Triangle::CollidingPoint(const Point& other) const
{
    return CheckTriangleAndPoint(*this, other);
}

void Triangle::Draw() const
{
    render->Triangle(position, pointA, pointB, pointC, color);
}
