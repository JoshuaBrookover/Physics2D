#pragma once
#include <CGUL.hpp>
#include "Render.hpp"

struct Circle;
struct AxisAlignedBox;
struct OrientedBox;

extern Render* render;

struct Collision
{
    enum
    {
        CIRCLE,
        AXIS_ALIGNED_BOX,
        ORIENTED_BOX
    };

    static void ProjectionOnAxis(const CGUL::Vector2* points, const CGUL::Size count, const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max);

    static bool CheckCircleAndCircle(const Circle& a, const Circle& b);
    static bool CheckCircleAndAxisAlignedBox(const Circle& circle, const AxisAlignedBox& box);
    static bool CheckCircleAndOrientedBox(const Circle& circle, const OrientedBox& box);
    static bool CheckAxisAlignedBoxAndAxisAlignedBox(const AxisAlignedBox& a, const AxisAlignedBox& b);
    static bool CheckAxisAlignedBoxAndOrientedBox(const AxisAlignedBox& aabb, const OrientedBox& obb);
    static bool CheckOrientedBoxAndOrientedBox(const OrientedBox& a, const OrientedBox& b);

    CGUL::Enum type;

    Collision(CGUL::Enum type);

    virtual void SetPosition(const CGUL::Vector2& position) = 0;
    virtual CGUL::Vector2 GetPosition() const = 0;

    virtual void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const = 0;
    virtual bool CollidingOnAxis(const Collision& other, const CGUL::Vector2& axis) const;
    virtual bool CollidingOnAxes(const Collision& other, CGUL::Vector2* axes, CGUL::Size count) const;

    virtual bool CollidingCircle(const Circle& other) const = 0;
    virtual bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const = 0;
    virtual bool CollidingOrientedBox(const OrientedBox& other) const = 0;

    virtual void Draw() const = 0;
};
