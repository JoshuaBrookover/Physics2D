#pragma once
#include <CGUL.hpp>
#include "Render.hpp"

extern Render* render;

class OrientedBox;

struct AxisAlignedBox
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

    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;

    void Draw() const;
};
