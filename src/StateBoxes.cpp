#include "StateBoxes.hpp"

StateBoxes::StateBoxes() :
    box1(CGUL::Vector2(0, 0), CGUL::Vector2(75, 75), 0),
    box2(CGUL::Vector2(400, 300), CGUL::Vector2(75, 75), 0)
{
    box1.color = CGUL::Colors::cornflowerBlue;
    box2.color = CGUL::Colors::cornflowerBlue;
}

StateBoxes::~StateBoxes()
{
}

void StateBoxes::Enter()
{
    render->SetClearColor(CGUL::Colors::darkBlue);
    window->SetTitle(U8("Boxes - Physics Stuff by Joshua \"jalb\" Brookover"));
}

void StateBoxes::Update(CGUL::Float32 deltaTime)
{
    //render->Box(CGUL::Vector2(100, 100), CGUL::Vector2(300, 300), CGUL::Colors::yellow);
    //render->Circle(CGUL::Vector2(450, 450), 50, CGUL::Colors::yellow);

    box1.position = stateMachine->GetMousePosition();

    static CGUL::Float32 timer = 0;
    timer += deltaTime * 3;

    box1.halfExtents = CGUL::Vector2(50, 50) + (CGUL::Vector2(25, 25) * CGUL::Math::Sin(timer));
    box1.orientation = CGUL::Math::Mod(box1.orientation + deltaTime, CGUL::Math::Tau< CGUL::Float32 >());

    //box2.orientation = CGUL::Math::Mod(box2.orientation + deltaTime * 0.34892f, CGUL::Math::Tau< CGUL::Float32 >());
    if (stateMachine->IsKeyDown('A'))
    {
        box2.orientation = CGUL::Math::Pi< CGUL::Float32 >();
    }
    else
    {
        box2.orientation = 0;
    }

    render->SetDoNotDraw(true);
    if (box1.CollidingOrientedBox(box2))
    {
        box1.color = CGUL::Colors::red;
        box2.color = CGUL::Colors::red;
    }
    else
    {
        box1.color = CGUL::Colors::cornflowerBlue;
        box2.color = CGUL::Colors::cornflowerBlue;
    }
    render->SetDoNotDraw(false);

    box1.Draw();
    box2.Draw();

    box1.CollidingOrientedBox(box2);

    CGUL::SCoord32 mousePos = stateMachine->GetMousePosition();
    render->Circle(box2.GetClosestPoint(mousePos), 3, CGUL::Colors::white);
}

void StateBoxes::Exit()
{
}
