#pragma once
#include <CGUL.hpp>
#include "Collision.hpp"
#include "Render.hpp"

extern Render* render;

struct Triangle : public Collision
{
    CGUL::Vector2 position;
    CGUL::Vector2 pointA;
    CGUL::Vector2 pointB;
    CGUL::Vector2 pointC;
    CGUL::Float32 orientation;

    Triangle();
    Triangle(const CGUL::Vector2& position, const CGUL::Vector2& pointA, const CGUL::Vector2& pointB, const CGUL::Vector2& pointC, CGUL::Float32 orientation);

    void SetPosition(const CGUL::Vector2& position);
    void SetPointA(const CGUL::Vector2& point);
    void SetPointB(const CGUL::Vector2& point);
    void SetPointC(const CGUL::Vector2& point);
    void SetOrientation(CGUL::Float32 orientation);

    CGUL::Vector2 GetPosition() const;
    CGUL::Vector2 GetPointA() const;
    CGUL::Vector2 GetPointB() const;
    CGUL::Vector2 GetPointC() const;
    CGUL::Float32 GetOrientation() const;

    CGUL::Vector2 GetClosestPoint(const CGUL::Vector2& position) const;

    void ProjectionOnAxis(const CGUL::Vector2& axis, CGUL::Float32* min, CGUL::Float32* max) const;

    CGUL::Matrix GetWorldMatrix() const;

    bool CollidingCircle(const Circle& other) const;
    bool CollidingAxisAlignedBox(const AxisAlignedBox& other) const;
    bool CollidingOrientedBox(const OrientedBox& other) const;
    bool CollidingLine(const Line& other) const;
    bool CollidingTriangle(const Triangle& other) const;

    void Draw() const;
};
