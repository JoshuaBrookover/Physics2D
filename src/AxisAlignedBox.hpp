#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct AxisAlignedBox : public Collision
{
    CGUL::Color color;
    CGUL::Vector2 position;
    CGUL::Vector2 extents;

    AxisAlignedBox();
    AxisAlignedBox(const CGUL::Vector2& position, const CGUL::Vector2& extents);

    void SetPosition(const CGUL::Vector2& position);
    void SetExtents(const CGUL::Vector2& extents);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetExtents() const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;
    bool CollidingOnAxis(const Collision& other, const CGUL::Vector2& axis) const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;

    void Draw() const;
};
