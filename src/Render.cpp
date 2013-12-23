#include "Render.hpp"
#include "State.hpp"
#include "StateMachine.hpp"
#include <GL/glew.h>

void Render::MakeShader()
{
    using namespace CGUL;

    // Create the shaders
    UInt vertexShader, fragmentShader;
    vertexShader = GL::CreateShader(GL_VERTEX_SHADER);
    fragmentShader = GL::CreateShader(GL_FRAGMENT_SHADER);

    // Set the shader sources
    GL::ShaderSource(vertexShader,
    "#version 120\n"
    "uniform mat4 orthoMatrix;\n"
    "uniform mat4 modelMatrix;\n"
    "uniform int shaderType;\n" // 0 = geometry, 1 = repositioned geometry, 2 = texture
    "uniform vec2 positions[20];\n"
    "attribute vec2 vertPosition;\n"
    "attribute vec2 vertTexCoord;\n"
    " varying vec2 fragTexCoord;\n"
    "void main(void)\n"
    "{\n"
    "    if (shaderType == 2)\n"
    "    {\n"
    "        gl_Position = (orthoMatrix * modelMatrix) * vec4(vertPosition, 0.0, 1.0);\n"
    "        fragTexCoord = vertTexCoord;\n"
    "    }\n"
    "    else if (shaderType == 1)\n"
    "    {\n"
    "        gl_Position = (orthoMatrix * modelMatrix) * vec4(positions[int(vertPosition.x)], 0.0, 1.0);\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        gl_Position = (orthoMatrix * modelMatrix) * vec4(vertPosition, 0.0, 1.0);\n"
    "    }\n"
    "}\n");
    GL::ShaderSource(fragmentShader,
    "#version 120\n"
    "uniform sampler2D texture;\n"
    "uniform vec4 color;\n"
    "uniform int shaderType;\n"
    "varying vec2 fragTexCoord;\n"
    "void main(void)\n"
    "{\n"
    "    if (shaderType == 2)\n"
    "    {\n"
    "        gl_FragColor = texture2D(texture, fragTexCoord);\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        gl_FragColor = color;\n"
    "    }\n"
    "}\n");

    // Compile the shaders
    GL::CompileShader(vertexShader);
    GL::CompileShader(fragmentShader);

    // Check if shaders compiled
    SInt status;
    GL::GetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        String log;
        GL::GetShaderInfoLog(vertexShader, &log);
        throw FatalException(U8("Failed to compile shader:\n") + log);
    }
    GL::GetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        String log;
        GL::GetShaderInfoLog(fragmentShader, &log);
        throw FatalException(U8("Failed to compile shader:\n") + log);
    }

    // Create the program
    shaderProgram = GL::CreateProgram();

    // Setup the attributes
    GL::BindAttribLocation(shaderProgram, GL::POSITION1, "vertPosition");
    GL::BindAttribLocation(shaderProgram, GL::TEXCOORD1, "vertTexCoord");

    // Link the program
    GL::AttachShader(shaderProgram, vertexShader);
    GL::AttachShader(shaderProgram, fragmentShader);
    GL::LinkProgram(shaderProgram);
    GL::GetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        String log;
        GL::GetProgramInfoLog(shaderProgram, &log);
        throw FatalException(U8("Failed to link program:\n") + log);
    }
    GL::ValidateProgram(shaderProgram);
    GL::GetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE)
    {
        String log;
        GL::GetProgramInfoLog(shaderProgram, &log);
        throw FatalException(U8("Failed to validate program:\n") + log);
    }

}

void Render::MakeSprite()
{
    using namespace CGUL;

    // Setup the buffer data
    Vector2 spritePositions[] = { Vector2(0.0f, 0.0f), Vector2(0.0f, 1.0f), Vector2(1.0f, 1.0f), Vector2(1.0f, 0.0f) };
    Vector2 spriteTexCoords[] = { Vector2(0.0f, 1.0f), Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector2(1.0f, 1.0f) };

    // Create the vertex array object
    GL::GenVertexArrays(1, &vertexArraySprite);
    GL::BindVertexArray(vertexArraySprite);

    // Setup the position buffer and attach it to the vertex array
    UInt buffer1;
    GL::GenBuffers(1, &buffer1);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer1);
    GL::BufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), spritePositions, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::POSITION1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::POSITION1);

    // Setup the texcoord buffer and attach it to the vertex array
    UInt buffer2;
    GL::GenBuffers(1, &buffer2);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer2);
    GL::BufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), spriteTexCoords, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::TEXCOORD1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::TEXCOORD1);

    // All done
    GL::BindVertexArray(0);
}

void Render::MakeBox()
{
    using namespace CGUL;

    // Setup the buffer data
    Vector2 boxPositions[] = { Vector2(-0.5f, -0.5f), Vector2(-0.5f, 0.5f), Vector2(0.5f, 0.5f), Vector2(0.5f, -0.5f) };

    // Create the vertex array object
    GL::GenVertexArrays(1, &vertexArrayBox);
    GL::BindVertexArray(vertexArrayBox);

    // Setup the position buffer and attach it to the vertex array
    UInt buffer1;
    GL::GenBuffers(1, &buffer1);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer1);
    GL::BufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vector2), boxPositions, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::POSITION1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::POSITION1);

    // All done
    GL::BindVertexArray(0);
}

void Render::MakeCircle()
{
    using namespace CGUL;

    // Calculate circle coordinates
    Vector2 circlePositions[circlePrecision + 2];
    circlePositions[0] = Vector2(0, 0);

    Float32 angle = 0;
    Float32 step = Math::Tau< Float32 >() / circlePrecision;
    for (UInt32 i = 1; i < circlePrecision + 2; i++)
    {
        circlePositions[i] = Vector2(Math::Cos(angle), Math::Sin(angle));
        angle += step;
    }

    // Create the vertex array object
    GL::GenVertexArrays(1, &vertexArrayCircle);
    GL::BindVertexArray(vertexArrayCircle);

    // Setup the position buffer and attach it to the vertex array
    UInt buffer1;
    GL::GenBuffers(1, &buffer1);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer1);
    GL::BufferData(GL_ARRAY_BUFFER, (circlePrecision + 2) * sizeof(Vector2), circlePositions, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::POSITION1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::POSITION1);

    // All done
    GL::BindVertexArray(0);
}

void Render::MakeLine()
{
    using namespace CGUL;

    // Setup the buffer data
    Vector2 linePositions[] = { Vector2(0, 0), Vector2(1, 1) };

    // Create the vertex array object
    GL::GenVertexArrays(1, &vertexArrayLine);
    GL::BindVertexArray(vertexArrayLine);

    // Setup the position buffer and attach it to the vertex array
    UInt buffer1;
    GL::GenBuffers(1, &buffer1);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer1);
    GL::BufferData(GL_ARRAY_BUFFER, 2 * sizeof(Vector2), linePositions, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::POSITION1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::POSITION1);

    // All done
    GL::BindVertexArray(0);
}

void Render::MakeTriangle()
{
    using namespace CGUL;

    // Setup the buffer data
    Vector2 trianglePositions[] = { Vector2(0, 0), Vector2(1, 1), Vector2(2, 2) };
    //Vector2 trianglePositions[] = { Vector2(-20, 0), Vector2(0, 40), Vector2(20, 0) };

    // Create the vertex array object
    GL::GenVertexArrays(1, &vertexArrayTriangle);
    GL::BindVertexArray(vertexArrayTriangle);

    // Setup the position buffer and attach it to the vertex array
    UInt buffer1;
    GL::GenBuffers(1, &buffer1);
    GL::BindBuffer(GL_ARRAY_BUFFER, buffer1);
    GL::BufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vector2), trianglePositions, GL_STATIC_DRAW);
    GL::VertexAttribPointer(GL::POSITION1, 2, GL_FLOAT, false, 0, 0);
    GL::EnableVertexAttribArray(GL::POSITION1);

    // All done
    GL::BindVertexArray(0);
}

Render::Render(CGUL::Window* window) :
    window(window),
    screenSpace(0, 0, 800, 600)
{
    context.Create(window);
    context.ClearColor(CGUL::Colors::black);

    CGUL::GL::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    CGUL::GL::Enable(GL_BLEND);
    CGUL::GL::Enable(GL_ALPHA_TEST);
    CGUL::GL::Enable(GL_TEXTURE_2D);

    MakeShader();
    MakeSprite();
    MakeBox();
    MakeCircle();
    MakeLine();
    MakeTriangle();
}

void Render::Update(State* state, StateMachine* stateMachine, CGUL::Float32 deltaTime)
{
    using namespace CGUL;

    context.Viewport(0, 0, window->GetWidth(), window->GetHeight());
    context.Clear(GL_COLOR_BUFFER_BIT);

    GL::UseProgram(shaderProgram);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "orthoMatrix"), 1, false, Matrix::MakeOrtho2D(screenSpace.x, screenSpace.z, screenSpace.y, screenSpace.w).GetData());

    if (state != NULL)
    {
        state->Update(deltaTime);
    }
    stateMachine->Draw(deltaTime);
    GL::UseProgram(0);
    context.SwapBuffers();
}

void Render::Reset()
{
    context.ClearColor(CGUL::Colors::black);
}

void Render::SetClearColor(const CGUL::Color& color)
{
    context.ClearColor(color);
}

void Render::SetScreenSpace(const CGUL::Vector4& screenSpace)
{
    this->screenSpace = screenSpace;
}

CGUL::UInt32 Render::LoadSprite(const CGUL::String& filename, CGUL::UCoord32* size)
{
    using namespace CGUL;

    Image image;
    image.Load(filename);

    if (size != NULL)
    {
        *size = UCoord32(image.GetWidth(), image.GetHeight());
    }

    UInt texture;
    GL::GenTextures(1, &texture);
    GL::BindTexture(GL_TEXTURE_2D, texture);
    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GL::TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GL::TexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    GL::PixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GL::TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetData<void>());
    GL::BindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void Render::FreeSprite(CGUL::UInt32 texture)
{
    // do stuff?
}

void Render::Sprite(CGUL::UInt32 texture, const CGUL::Vector2& position, const CGUL::Vector2& size)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeScaling(size);
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 2);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "texture"), 0);
    GL::ActiveTexture(GL_TEXTURE0);
    GL::BindTexture(GL_TEXTURE_2D, texture);
    GL::BindVertexArray(vertexArraySprite);
    GL::DrawArrays(GL_QUADS, 0, 4);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 0);
    GL::BindVertexArray(0);
}

void Render::Box(const CGUL::Vector2& position, const CGUL::Vector2& size, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeScaling(size);
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::BindVertexArray(vertexArrayBox);
    GL::DrawArrays(GL_QUADS, 0, 4);
    GL::BindVertexArray(0);
}

void Render::Box(const CGUL::Vector2& position, const CGUL::Vector2& size, CGUL::Float32 orientation, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeScaling(size);
    model = model * Matrix::MakeRotation(orientation);
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::BindVertexArray(vertexArrayBox);
    GL::DrawArrays(GL_QUADS, 0, 4);
    GL::BindVertexArray(0);
}

void Render::Circle(const CGUL::Vector2& position, CGUL::Float32 radius, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeScaling(Vector2(radius, radius));
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::BindVertexArray(vertexArrayCircle);
    GL::DrawArrays(GL_TRIANGLE_FAN, 0, circlePrecision + 2);
    GL::BindVertexArray(0);
}

void Render::Circle(const CGUL::Vector2& position, CGUL::Float32 radius, CGUL::Float32 orientation, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeScaling(Vector2(radius, radius));
    model = model * Matrix::MakeRotation(orientation);
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::BindVertexArray(vertexArrayCircle);
    GL::DrawArrays(GL_TRIANGLE_FAN, 0, circlePrecision + 2);
    GL::BindVertexArray(0);
}

void Render::Line(const CGUL::Vector2& start, const CGUL::Vector2& end, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model = Matrix::Identity();
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 1);
    CGUL::Vector2 positions[2] = { start, end };
    GL::Uniform2fv(GL::GetUniformLocation(shaderProgram, "positions"), 2, positions);
    GL::BindVertexArray(vertexArrayLine);
    GL::DrawArrays(GL_LINES, 0, 2);
    GL::BindVertexArray(0);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 0);
}

void Render::Triangle(const CGUL::Vector2& position, const CGUL::Vector2& pointA, const CGUL::Vector2& pointB, const CGUL::Vector2& pointC, const CGUL::Color& color)
{
    using namespace CGUL;

    if (doNotDraw)
    {
        return;
    }

    Matrix model;
    model = model * Matrix::MakeTranslation(position);
    GL::UniformMatrix4fv(GL::GetUniformLocation(shaderProgram, "modelMatrix"), 1, false, model.GetData());
    GL::Uniform4f(GL::GetUniformLocation(shaderProgram, "color"), color);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 1);
    CGUL::Vector2 positions[3] = { pointA, pointB, pointC };
    GL::Uniform2fv(GL::GetUniformLocation(shaderProgram, "positions"), 3, positions);
    GL::BindVertexArray(vertexArrayTriangle);
    GL::DrawArrays(GL_TRIANGLES, 0, 3);
    GL::BindVertexArray(0);
    GL::Uniform1i(GL::GetUniformLocation(shaderProgram, "shaderType"), 0);
}

void Render::SetDoNotDraw(CGUL::Boolean draw)
{
    doNotDraw = draw;
}
