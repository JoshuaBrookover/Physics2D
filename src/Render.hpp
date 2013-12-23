#pragma once
#include <CGUL.hpp>

class State;
class StateMachine;

class Render
{
    static const CGUL::UInt32 circlePrecision = 16;

    CGUL::UInt32 shaderProgram;
    CGUL::UInt32 vertexArraySprite;
    CGUL::UInt32 vertexArrayBox;
    CGUL::UInt32 vertexArrayCircle;
    CGUL::UInt32 vertexArrayLine;
    CGUL::UInt32 vertexArrayTriangle;

    CGUL::Window* window;
    CGUL::OpenGL::Context context;

    CGUL::Vector4 screenSpace;

    bool doNotDraw;

    void MakeShader();
    void MakeSprite();
    void MakeBox();
    void MakeCircle();
    void MakeLine();
    void MakeTriangle();
public:
    Render(CGUL::Window* window);

    void Update(State* state, StateMachine* stateMachine, CGUL::Float32 deltaTime);
    void Reset();

    void SetClearColor(const CGUL::Color& color);
    void SetScreenSpace(const CGUL::Vector4& screenSpace);

    CGUL::UInt32 LoadSprite(const CGUL::String& filename, CGUL::UCoord32* size);
    void FreeSprite(CGUL::UInt32 texture);

    void Sprite(CGUL::UInt32 texture, const CGUL::Vector2& position, const CGUL::Vector2& size);
    void Box(const CGUL::Vector2& position, const CGUL::Vector2& size, const CGUL::Color& color);
    void Box(const CGUL::Vector2& position, const CGUL::Vector2& size, CGUL::Float32 orientation, const CGUL::Color& color);
    void Circle(const CGUL::Vector2& position, CGUL::Float32 radius, const CGUL::Color& color);
    void Circle(const CGUL::Vector2& position, CGUL::Float32 radius, CGUL::Float32 orientation, const CGUL::Color& color);
    void Line(const CGUL::Vector2& start, const CGUL::Vector2& end, const CGUL::Color& color);
    void Triangle(const CGUL::Vector2& position, const CGUL::Vector2& pointA, const CGUL::Vector2& pointB, const CGUL::Vector2& pointC, const CGUL::Color& color);

    void SetDoNotDraw(CGUL::Boolean draw);
};
