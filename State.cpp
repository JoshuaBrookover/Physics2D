#include "State.hpp"

State::State()
{
}

State::~State()
{
}

void State::Setup(StateMachine* stateMachine, Render* render, CGUL::Window* window)
{
    this->stateMachine = stateMachine;
    this->render = render;
    this->window = window;
}
