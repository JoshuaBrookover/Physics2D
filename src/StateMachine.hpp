#pragma once
#include <CGUL.hpp>

class State;
class Render;

extern Render* render;

class StateMachine
{
    static void KeyButtonEvent(const CGUL::WindowKeyButtonEvent& event, void* userData);
    static void MouseButtonEvent(const CGUL::WindowMouseButtonEvent& event, void* userData);
    static void MouseMoveEvent(const CGUL::WindowMouseMoveEvent& event, void* userData);

    State* currentState;
    State* queuedState;

    CGUL::Window window;
    CGUL::Timer timer;

    enum InputState
    {
        INPUT_DOWN = 1,
        INPUT_HELD = 2
    };
    CGUL::Byte keys[256];
    CGUL::Byte buttons[256];

    CGUL::SCoord32 mousePosition;

    CGUL::UInt32 banner;
    CGUL::UCoord32 bannerSize;
public:
    StateMachine();
    ~StateMachine();

    void ChangeState(State* newState);

    void SetTitle(const CGUL::String& title);

    void Initialize();
    bool IsRunning() const;
    void Update();
    void Draw(CGUL::Float32 deltaTime);
    void Reset();
    void Exit();

    CGUL::SCoord32 GetMousePosition() const;

    bool IsKeyDown(CGUL::Byte key) const;
    bool IsKeyPressed(CGUL::Byte key) const;
    bool IsKeyReleased(CGUL::Byte key) const;

    bool IsButtonDown(CGUL::Byte button) const;
    bool IsButtonPressed(CGUL::Byte button) const;
    bool IsButtonReleased(CGUL::Byte button) const;
};
