#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct AxisAlignedBox : public Collision
{
    CGUL::Vector2 position;
    CGUL::Vector2 halfExtents;

    AxisAlignedBox();
    AxisAlignedBox(const CGUL::Vector2& position, const CGUL::Vector2& halfExtents);

    void SetPosition(const CGUL::Vector2& position);
    void SetHalfExtents(const CGUL::Vector2& halfExtents);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetExtents() const;

    CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;

    CGUL::Matrix GetWorldMatrix() const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;
    bool CollidingLine(const Line& other) const;

    void Draw() const;
};
