#include "Collision.hpp"

void Collision::ProjectionOnAxis(const CGUL::Vector2* points, const CGUL::Size count, const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max)
{
    CGUL::Vector2 point = points[0];
    point = points[0];
    CGUL::Float32 dotProduct = CGUL::Vector2::DotProduct(axis, point);
    render->Line(point, point + CGUL::Vector2(5, 5), CGUL::Colors::white);
    *min = *max = dotProduct;
    for (CGUL::Byte i = 1; i < count; i++)
    {
        point = points[i];
        render->Line(point, point + CGUL::Vector2(5, 5), CGUL::Colors::white);

        dotProduct = CGUL::Vector2::DotProduct(axis, point);

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

Collision::Collision(CGUL::Enum type) :
    type(type)
{
}

bool Collision::CollidingOnAxis(const Collision& other, const CGUL::Vector2& axis) const
{
    CGUL::Float32 min, max, otherMin, otherMax;
    ProjectionOnAxis(axis, &min, &max);
    other.ProjectionOnAxis(axis, &otherMin, &otherMax);

    return (min <= otherMax && max >= otherMin);
}

bool Collision::CollidingOnAxes(const Collision& other, CGUL::Vector2* axes, CGUL::Size count) const
{
    for (CGUL::Size i = 0; i < count; i++)
    {
        if (!CollidingOnAxis(other, axes[i]))
        {
            return false;
        }
    }
    return true;
}
