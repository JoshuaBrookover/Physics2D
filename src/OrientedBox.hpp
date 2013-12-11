#pragma once
#include <CGUL.hpp>
#include "Render.hpp"

extern Render* render;

class AxisAlignedBox;

struct OrientedBox
{
    CGUL::Color color;
    CGUL::Vector2 position;
    CGUL::Vector2 extents;
    CGUL::Float32 orientation;

    OrientedBox();
    OrientedBox(const CGUL::Vector2& position, const CGUL::Vector2& extents, CGUL::Float32 orientation);

    void SetPosition(const CGUL::Vector2& position);
    void SetExtents(const CGUL::Vector2& extents);
    void SetOrientation(CGUL::Float32 orientation);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetExtents() const;
    CGUL::Float32 GetOrientation() const;

    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;

    void Draw() const;
};
