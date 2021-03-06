#pragma once
#include <CGUL.hpp>
#include "Render.hpp"

struct Circle;
struct AxisAlignedBox;
struct OrientedBox;
struct Line;
struct Triangle;
struct Point;

extern Render* render;

struct Collision
{
    enum
    {
        CIRCLE,
        AXIS_ALIGNED_BOX,
        ORIENTED_BOX,
        LINE,
        TRIANGLE,
        POINT
    };

    static void ProjectionOnAxis(const CGUL::Vector2* points, const CGUL::Size count, const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max);

    static bool CheckCircleAndCircle(const Circle& a, const Circle& b);
    static bool CheckCircleAndAxisAlignedBox(const Circle& circle, const AxisAlignedBox& box);
    static bool CheckCircleAndOrientedBox(const Circle& circle, const OrientedBox& box);
    static bool CheckCircleAndLine(const Circle& circle, const Line& line);
    static bool CheckCircleAndTriangle(const Circle& circle, const Triangle& triangle);
    static bool CheckCircleAndPoint(const Circle& circle, const Point& point);
    static bool CheckAxisAlignedBoxAndAxisAlignedBox(const AxisAlignedBox& a, const AxisAlignedBox& b);
    static bool CheckAxisAlignedBoxAndOrientedBox(const AxisAlignedBox& aabb, const OrientedBox& obb);
    static bool CheckAxisAlignedBoxAndLine(const AxisAlignedBox& box, const Line& line);
    static bool CheckAxisAlignedBoxAndTriangle(const AxisAlignedBox& box, const Triangle& triangle);
    static bool CheckAxisAlignedBoxAndPoint(const AxisAlignedBox& box, const Point& point);
    static bool CheckOrientedBoxAndOrientedBox(const OrientedBox& a, const OrientedBox& b);
    static bool CheckOrientedBoxAndLine(const OrientedBox& box, const Line& line);
    static bool CheckOrientedBoxAndTriangle(const OrientedBox& box, const Triangle& triangle);
    static bool CheckOrientedBoxAndPoint(const OrientedBox& box, const Point& point);
    static bool CheckLineAndLine(const Line& a, const Line& b);
    static bool CheckLineAndTriangle(const Line& line, const Triangle& triangle);
    static bool CheckLineAndPoint(const Line& line, const Point& point);
    static bool CheckTriangleAndTriangle(const Triangle& a, const Triangle& b);
    static bool CheckTriangleAndPoint(const Triangle& triangle, const Point& point);
    static bool CheckPointAndPoint(const Point& a, const Point& b);

    CGUL::Enum type;
    CGUL::Color color;

    Collision(CGUL::Enum type);

    virtual void SetPosition(const CGUL::Vector2& position) = 0;
    virtual CGUL::Vector2 GetPosition() const = 0;

    virtual CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const = 0;

    virtual CGUL::Matrix GetWorldMatrix() const = 0;

    virtual void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const = 0;
    virtual bool CollidingOnAxis(const Collision& other, const CGUL::Vector2& axis) const;
    virtual bool CollidingOnAxes(const Collision& other, CGUL::Vector2* axes, CGUL::Size count) const;

    virtual bool CollidingCircle(const Circle& other) const = 0;
    virtual bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const = 0;
    virtual bool CollidingOrientedBox(const OrientedBox& other) const = 0;
    virtual bool CollidingLine(const Line& other) const = 0;
    virtual bool CollidingTriangle(const Triangle& other) const = 0;
    virtual bool CollidingPoint(const Point& point) const = 0;

    bool Colliding(const Collision* other) const;

    virtual void Draw() const = 0;
};
