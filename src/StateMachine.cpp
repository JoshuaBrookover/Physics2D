#include "StateMachine.hpp"
#include "State.hpp"
#include "Render.hpp"

#include "StateBoxes.hpp"
#include "StateCircles.hpp"
#include "StateTest.hpp"

Render* render;

void StateMachine::KeyButtonEvent(const CGUL::WindowKeyButtonEvent& event, void* userData)
{
    StateMachine* stateMachine = (StateMachine*)userData;
    if (event.key < 256)
    {
        CGUL::Byte& key = stateMachine->keys[event.key];
        key = (event.pressed ? key | INPUT_DOWN : key & ~INPUT_DOWN);
    }
}

void StateMachine::MouseButtonEvent(const CGUL::WindowMouseButtonEvent& event, void* userData)
{
    StateMachine* stateMachine = (StateMachine*)userData;
    if (event.button < 3)
    {
        CGUL::Byte& button = stateMachine->buttons[event.button];
        button = (event.pressed ? button | INPUT_DOWN : button & ~INPUT_DOWN);
    }
}

void StateMachine::MouseMoveEvent(const CGUL::WindowMouseMoveEvent& event, void* userData)
{
    StateMachine* stateMachine = (StateMachine*)userData;
    CGUL::Vector2 relativeSize(800.0f / stateMachine->window.GetWidth(), 600.0f / stateMachine->window.GetHeight());
    stateMachine->mousePosition = event.location;
    stateMachine->mousePosition = CGUL::SCoord32(stateMachine->mousePosition.x * relativeSize.x, stateMachine->mousePosition.y * relativeSize.y);
}

StateMachine::StateMachine() :
    currentState(NULL),
    queuedState(NULL)
{
    render = NULL;
    CGUL::Memory::ZeroData(keys, 256);
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
    window.SetCursorShow(false);

    window.onKeyButton.AddEvent(KeyButtonEvent, this);
    window.onMouseButton.AddEvent(MouseButtonEvent, this);
    window.onMouseMove.AddEvent(MouseMoveEvent, this);

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

    if (IsKeyPressed('1'))
    {
        ChangeState(new StateBoxes);
    }
    else if (IsKeyPressed('2'))
    {
        ChangeState(new StateCircles);
    }
    else if (IsKeyPressed('3'))
    {
        ChangeState(new StateTest);
    }

    for (CGUL::UInt32 i = 0; i < 256; i++)
    {
        if (keys[i] & INPUT_DOWN)
        {
            keys[i] |= INPUT_HELD;
        }
        else
        {
            keys[i] &= ~INPUT_HELD;
        }
    }

    for (CGUL::UInt32 i = 0; i < 3; i++)
    {
        if (buttons[i] & INPUT_DOWN)
        {
            buttons[i] |= INPUT_HELD;
        }
        else
        {
            buttons[i] &= ~INPUT_HELD;
        }
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

bool StateMachine::IsKeyDown(CGUL::Byte key) const
{
    return (keys[key] & INPUT_DOWN) != 0;
}

bool StateMachine::IsKeyPressed(CGUL::Byte key) const
{
    return (keys[key] & INPUT_DOWN) && !(keys[key] & INPUT_HELD);
}

bool StateMachine::IsKeyReleased(CGUL::Byte key) const
{
    return (keys[key] & INPUT_HELD) && !(keys[key] & INPUT_DOWN);
}

bool StateMachine::IsButtonDown(CGUL::Byte button) const
{
    return (buttons[button] & INPUT_DOWN) != 0;
}

bool StateMachine::IsButtonPressed(CGUL::Byte button) const
{
    return (buttons[button] & INPUT_DOWN) && !(buttons[button] & INPUT_HELD);
}

bool StateMachine::IsButtonReleased(CGUL::Byte button) const
{
    return (buttons[button] & INPUT_HELD) && !(buttons[button] & INPUT_DOWN);
}
