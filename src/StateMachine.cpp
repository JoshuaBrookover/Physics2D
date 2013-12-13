#include "StateMachine.hpp"
#include "State.hpp"
#include "Render.hpp"

Render* render;
StateMachine* stateMachine;

void StateMachine::KeyButtonEvent(const CGUL::WindowKeyButtonEvent& event)
{
}

void StateMachine::MouseButtonEvent(const CGUL::WindowMouseButtonEvent& event)
{
}

void StateMachine::MouseMoveEvent(const CGUL::WindowMouseMoveEvent& event)
{
    if (stateMachine != NULL)
    {
        CGUL::Vector2 relativeSize(800.0f / stateMachine->window.GetWidth(), 600.0f / stateMachine->window.GetHeight());
        stateMachine->mousePosition = event.location;
        stateMachine->mousePosition = CGUL::SCoord32(stateMachine->mousePosition.x * relativeSize.x, stateMachine->mousePosition.y * relativeSize.y);
    }
}

StateMachine::StateMachine() :
    currentState(NULL),
    queuedState(NULL)
{
    render = NULL;
    stateMachine = this;
}

StateMachine::~StateMachine()
{
}

void StateMachine::ChangeState(State* newState)
{
    queuedState = newState;
}

void StateMachine::Initialize()
{
    CGUL::WindowStyle style;
    style.title = U8("");
    style.size = CGUL::UCoord32(800, 600);
    style.backgroundColor = CGUL::Colors::black;
    window.Create(style);

    window.onKeyButton += KeyButtonEvent;
    window.onMouseButton += MouseButtonEvent;
    window.onMouseMove += MouseMoveEvent;

    render = new Render(&window);

    timer.Start();
}

bool StateMachine::IsRunning() const
{
    return window.IsOpen();
}

void StateMachine::Update()
{
    CGUL::Timer::Sleep(1);

    if (render == NULL)
    {
        return;
    }

    if (queuedState != NULL)
    {
        if (currentState != NULL)
        {
            currentState->Exit();
        }
        delete currentState;
        currentState = queuedState;
        Reset();
        if (currentState != NULL)
        {
            currentState->Setup(this, render, &window);
            currentState->Enter();
        }
        queuedState = NULL;
    }
    CGUL::Float64 deltaTime = timer.GetDeltaTime();
    CGUL::Window::Update();
    render->Update(currentState, (CGUL::Float32)deltaTime);
}

void StateMachine::Reset()
{
    render->Reset();
    window.SetTitle(U8(""));
}

void StateMachine::Exit()
{
    if (currentState != NULL)
    {
        currentState->Exit();
    }
    window.Close();
}

CGUL::SCoord32 StateMachine::GetMousePosition() const
{
    return mousePosition;
}
