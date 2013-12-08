#include "TestState.hpp"

TestState::TestState()
{
}

TestState::~TestState()
{
}

void TestState::Enter()
{
    render->SetClearColor(CGUL::Colors::darkBlue);
    window->SetTitle(U8("Physics Stuff by Joshua \"jalb\" Brookover"));
}

void TestState::Update(CGUL::Float32 deltaTime)
{
}

void TestState::Draw() const
{
    render->Box(CGUL::Vector2(100, 100), CGUL::Vector2(300, 300), CGUL::Colors::yellow);
    render->Circle(CGUL::Vector2(450, 450), 50, CGUL::Colors::yellow);
    render->Line(CGUL::Vector2(0, 0), CGUL::Vector2(100, 100), CGUL::Colors::yellow);
}

void TestState::Exit()
{
}
