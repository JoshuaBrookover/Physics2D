#include "StateTest.hpp"
#include "Circle.hpp"
#include "AxisAlignedBox.hpp"
#include "OrientedBox.hpp"
#include "Line.hpp"
#include "Triangle.hpp"

StateTest::StateTest() :
    drag(NULL)
{
}

StateTest::~StateTest()
{
}

void StateTest::Enter()
{
    using namespace CGUL;

    render->SetClearColor(CGUL::Colors::darkBlue);
    stateMachine->SetTitle(U8("Test"));

    objects.push_back(new AxisAlignedBox(Vector2(100, 100), Vector2(50, 50)));
    objects.push_back(new OrientedBox(Vector2(150, 150), Vector2(50, 50), 90));
    objects.push_back(new Circle(Vector2(250, 350), 90, 0));
    //objects.push_back(new Triangle(Vector2(400, 300), Vector2(-25, 0), Vector2(0, 50), Vector2(25, 0), 0));
    objects.push_back(new Triangle(Vector2(400, 200), Vector2(-60, 0), Vector2(0, 120), Vector2(60, 0), 0));
}

void StateTest::Update(CGUL::Float32 deltaTime)
{
    using namespace CGUL;

    SCoord32 mousePos = stateMachine->GetMousePosition();
    Color mouseColor = Colors::red;
    Float32 mouseSize = 2;

    static Float32 timer = 0;
    timer += deltaTime;

    OrientedBox* wee = (OrientedBox*)objects[1];
    wee->orientation += deltaTime * 3;
    wee->halfExtents = Vector2(75, 75);

    Circle* circle = (Circle*)objects[2];
    circle->orientation += deltaTime * 3;

    for (CGUL::Vector< Collision* >::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        (*itr)->color = Colors::cornflowerBlue;

        if ((SCoord32)(*itr)->GetClosestPoint(mousePos) == mousePos)
        {
            mouseColor = Colors::green;
            mouseSize += 2;

            if (mouseSize == 4 && stateMachine->IsButtonPressed(0))
            {
                drag = *itr;
                Matrix inverseWorld = (*itr)->GetWorldMatrix().GetInverse();
                offset = mousePos;
                offset *= inverseWorld;
                offset *= -1;
            }
        }
    }
    if (!stateMachine->IsButtonDown(0))
    {
        drag = NULL;
    }

    if (drag != NULL)
    {
        mouseColor = Colors::yellow;
        mouseSize = 1;

        drag->SetPosition(mousePos);
        Vector2 a = offset;
        a *= drag->GetWorldMatrix();
        drag->SetPosition(a);
    }

    for (CGUL::Vector< Collision* >::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        for (CGUL::Vector< Collision* >::iterator other = itr + 1; other != objects.end(); other++)
        {
            if ((*itr)->Colliding(*other))
            {
                (*itr)->color = Colors::red;
                (*other)->color = Colors::red;
            }
        }
    }

    for (CGUL::Vector< Collision* >::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        (*itr)->Draw();
    }

    for (CGUL::Vector< Collision* >::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        render->Circle((*itr)->GetClosestPoint(mousePos), 2, CGUL::Colors::white);
    }

    render->Circle(mousePos, mouseSize, mouseColor);
}

void StateTest::Exit()
{
    for (CGUL::Vector< Collision* >::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        delete *itr;
    }
}
