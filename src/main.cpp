#include "StateMachine.hpp"
#include "TestState.hpp"

int main()
{
    StateMachine stateMachine;
    stateMachine.Initialize();
    stateMachine.ChangeState(new TestState());
    while (stateMachine.IsRunning())
    {
        stateMachine.Update();
    }
    stateMachine.Exit();
}
