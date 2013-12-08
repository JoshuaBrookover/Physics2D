#include "StateMachine.hpp"
#include "State.hpp"
#include "Render.hpp"

StateMachine::StateMachine() :
    currentState(NULL),
    queuedState(NULL),
    render(NULL)
{
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
    CGUL::Float32 deltaTime = timer.GetDeltaTime();
    CGUL::Window::Update();
    if (currentState != NULL)
    {
        currentState->Update(deltaTime);
    }
    render->Update(currentState);
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
