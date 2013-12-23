#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct OrientedBox : public Collision
{
    CGUL::Vector2 position;
    CGUL::Vector2 halfExtents;
    CGUL::Float32 orientation;

    OrientedBox();
    OrientedBox(const CGUL::Vector2& position, const CGUL::Vector2& halfExtents, CGUL::Float32 orientation);

    void SetPosition(const CGUL::Vector2& position);
    void SetHalfExtents(const CGUL::Vector2& halfExtents);
    void SetOrientation(CGUL::Float32 orientation);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetHalfExtents() const;
    CGUL::Float32 GetOrientation() const;

    CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const;

    CGUL::Matrix GetWorldMatrix() const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;
    bool CollidingLine(const Line& other) const;
    bool CollidingTriangle(const Triangle& other) const;
    bool CollidingPoint(const Point& other) const;

    void Draw() const;
};
