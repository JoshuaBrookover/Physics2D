#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct Line : public Collision
{
    CGUL::Color color;
    CGUL::Vector2 start;
    CGUL::Vector2 end;

    Line();
    Line(const CGUL::Vector2& start, const CGUL::Vector2& end);

    void SetPosition(const CGUL::Vector2& position);
    void SetStart(const CGUL::Vector2& start);
    void SetEnd(const CGUL::Vector2& end);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetStart() const;
    CGUL::Vector2 GetEnd() const;

    CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;
    bool CollidingLine(const Line& other) const;

    void Draw() const;
};
