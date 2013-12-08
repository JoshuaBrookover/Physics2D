#pragma once
#include <CGUL.hpp>

class State;

class Render
{
    static const CGUL::UInt32 circlePrecision = 32;

    CGUL::UInt32 shaderProgram;
    CGUL::UInt32 vertexArrayBox;
    CGUL::UInt32 vertexArrayCircle;
    CGUL::UInt32 vertexArrayLine;

    CGUL::Window* window;
    CGUL::OpenGL::Context context;

    CGUL::SRect32 viewport;
    CGUL::Vector4 screenSpace;

    void MakeShader();
    void MakeBox();
    void MakeCircle();
    void MakeLine();
public:
    Render(CGUL::Window* window);

    void Update(const State* state);
    void Reset();

    void SetClearColor(const CGUL::Color& color);
    void SetViewport(const CGUL::SRect32& viewport);
    void SetScreenSpace(const CGUL::Vector4& screenSpace);

    void Box(const CGUL::Vector2& position, const CGUL::Vector2& size, const CGUL::Color& color);
    void Circle(const CGUL::Vector2& position, CGUL::Float32 radius, const CGUL::Color& color);
    void Line(const CGUL::Vector2& start, const CGUL::Vector2& end, const CGUL::Color& color);
};
