#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct Circle : public Collision
{
    CGUL::Vector2 position;
    CGUL::Float32 radius;
    CGUL::Float32 orientation;

    Circle();
    Circle(const CGUL::Vector2& position, CGUL::Float32 radius, CGUL::Float32 orientation);

    void SetPosition(const CGUL::Vector2& position);
    void SetRadius(CGUL::Float32 radius);

    CGUL::Vector2 GetPosition() const;
    CGUL::Float32 GetRadius() const;

    CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;

    CGUL::Matrix GetWorldMatrix() const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;
    bool CollidingLine(const Line& other) const;
    bool CollidingTriangle(const Triangle& other) const;
    bool CollidingPoint(const Point& other) const;

    void Draw() const;
};
