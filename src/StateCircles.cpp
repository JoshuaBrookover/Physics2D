#include "StateCircles.hpp"

struct MovingCircle : public Circle
{
    CGUL::Vector2 velocity;

    MovingCircle() :
        Circle()
    {
    }

    MovingCircle(const CGUL::Vector2& position, CGUL::Float32 radius, const CGUL::Vector2& velocity) :
        Circle(position, radius, 0),
        velocity(velocity)
    {
    }
};

StateCircles::StateCircles()
{
}

StateCircles::~StateCircles()
{
}

void StateCircles::Enter()
{
    render->SetClearColor(CGUL::Colors::darkBlue);
    window->SetTitle(U8("Circles - Physics Stuff by Joshua \"jalb\" Brookover"));

    CGUL::Random random;
    for (int i = 0; i < 10; i++)
    {
        MovingCircle* circle = new MovingCircle;
        circle->position = CGUL::Vector2(random.GetInteger() % 800, random.GetInteger() % 600);
        circle->radius = 20 + random.GetInteger() % 40;
        circle->velocity = CGUL::Vector2::FromAngle(random.GetDecimal() * CGUL::Math::Tau< CGUL::Float32 >(), 2);
        circles.push_back(circle);
    }
}

void StateCircles::Update(CGUL::Float32 deltaTime)
{
    static CGUL::Float32 timer = 0;
    timer += deltaTime * 3;

    box.halfExtents = CGUL::Vector2(50, 50) + (CGUL::Vector2(25, 25) * CGUL::Math::Sin(timer));
    box.orientation = CGUL::Math::Mod(box.orientation + deltaTime, CGUL::Math::Tau< CGUL::Float32 >());
    box.position = stateMachine->GetMousePosition();

    render->SetDoNotDraw(true);
    for (CGUL::Vector< MovingCircle* >::iterator itr = circles.begin(); itr != circles.end(); itr++)
    {
        if ((*itr)->position.x < 0 || (*itr)->position.x > 800)
        {
            (*itr)->velocity.x *= -1;
        }
        if ((*itr)->position.y < 0 || (*itr)->position.y > 600)
        {
            (*itr)->velocity.y *= -1;
        }
        (*itr)->position += (*itr)->velocity;
        (*itr)->color = CGUL::Colors::cornflowerBlue;
    }

    for (CGUL::Vector< MovingCircle* >::iterator itr = circles.begin(); itr != circles.end(); itr++)
    {
        for (CGUL::Vector< MovingCircle* >::iterator other = itr + 1; other != circles.end(); other++)
        {
            if ((*itr)->CollidingCircle(*(*other)))
            {
                (*itr)->color = CGUL::Colors::red;
                (*other)->color = CGUL::Colors::red;
            }
        }
    }
    render->SetDoNotDraw(false);

    box.color = CGUL::Colors::cornflowerBlue;
    for (CGUL::Vector< MovingCircle* >::iterator itr = circles.begin(); itr != circles.end(); itr++)
    {
        if (box.CollidingCircle(*(*itr)))
        {
            box.color = CGUL::Colors::red;
            (*itr)->color = CGUL::Colors::red;
        }
        (*itr)->Draw();
    }

    CGUL::SCoord32 mousePos = stateMachine->GetMousePosition();
    for (CGUL::Vector< MovingCircle* >::iterator itr = circles.begin(); itr != circles.end(); itr++)
    {
        render->Circle((*itr)->GetClosestPoint(mousePos), 3, CGUL::Colors::white);
    }
    box.Draw();
}

void StateCircles::Exit()
{
    for (CGUL::Vector< MovingCircle* >::iterator itr = circles.begin(); itr != circles.end(); itr++)
    {
        delete *itr;
    }
}
