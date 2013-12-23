#include "StateBoxes.hpp"

StateBoxes::StateBoxes() :
    box1(CGUL::Vector2(0, 0), CGUL::Vector2(75, 75), 0),
    box2(CGUL::Vector2(400, 300), CGUL::Vector2(75, 100), 0),
    box3(CGUL::Vector2(600, 150), CGUL::Vector2(50, 40))
{
    box1.color = CGUL::Colors::cornflowerBlue;
    box2.color = CGUL::Colors::cornflowerBlue;
    line.color = CGUL::Colors::white;
    circle.color = CGUL::Colors::cornflowerBlue;
}

StateBoxes::~StateBoxes()
{
}

void StateBoxes::Enter()
{
    render->SetClearColor(CGUL::Colors::darkBlue);
    stateMachine->SetTitle(U8("Boxes"));
}

void StateBoxes::Update(CGUL::Float32 deltaTime)
{
    //render->Box(CGUL::Vector2(100, 100), CGUL::Vector2(300, 300), CGUL::Colors::yellow);
    //render->Circle(CGUL::Vector2(450, 450), 50, CGUL::Colors::yellow);

    CGUL::SCoord32 mousePosition = stateMachine->GetMousePosition();
    if (stateMachine->IsKeyDown('E'))
    {
        box1.position = mousePosition;
    }
    if (stateMachine->IsKeyDown('O'))
    {
        line.start = mousePosition;
    }
    if (stateMachine->IsKeyDown('P'))
    {
        line.end = mousePosition;
    }
    if (stateMachine->IsKeyDown('C'))
    {
        circle.position = mousePosition;
    }
    if (stateMachine->IsKeyDown('V'))
    {
        circle.radius = CGUL::Vector2::Distance(circle.position, mousePosition);
    }

    static CGUL::Float32 timer = 0;
    timer += deltaTime * 3;

    box1.halfExtents = CGUL::Vector2(50, 50) + (CGUL::Vector2(25, 25) * CGUL::Math::Sin(timer));
    box1.orientation = CGUL::Math::Mod(box1.orientation + deltaTime, CGUL::Math::Tau< CGUL::Float32 >());

    box2.orientation = CGUL::Math::Mod(box2.orientation + deltaTime * 0.34892f, CGUL::Math::Tau< CGUL::Float32 >());
    /*if (stateMachine->IsKeyDown('A'))
    {
        box2.orientation = CGUL::Math::Pi< CGUL::Float32 >();
    }
    else
    {
        box2.orientation = 0;
    }*/

    render->SetDoNotDraw(true);
    box1.color = CGUL::Colors::cornflowerBlue;
    box2.color = CGUL::Colors::cornflowerBlue;
    box3.color = CGUL::Colors::cornflowerBlue;
    if (box1.CollidingOrientedBox(box2))
    {
        box1.color = CGUL::Colors::red;
        box2.color = CGUL::Colors::red;
    }
    if (box1.CollidingAxisAlignedBox(box3))
    {
        box1.color = CGUL::Colors::red;
        box3.color = CGUL::Colors::red;
    }
    render->SetDoNotDraw(false);

    box1.Draw();
    box2.Draw();
    box3.Draw();
    line.Draw();
    circle.Draw();

    box1.CollidingOrientedBox(box2);

    CGUL::SCoord32 mousePos = stateMachine->GetMousePosition();
    render->Circle(box1.GetClosestPoint(mousePos), 7, CGUL::Colors::green);
    render->Circle(box2.GetClosestPoint(mousePos), 7, CGUL::Colors::green);
    render->Circle(box3.GetClosestPoint(mousePos), 7, CGUL::Colors::green);
    render->Circle(line.GetClosestPoint(mousePos), 7, CGUL::Colors::green);
    render->Circle(circle.GetClosestPoint(mousePos), 7, CGUL::Colors::green);

    render->Circle(mousePos, 2, CGUL::Colors::red);
}

void StateBoxes::Exit()
{
}
